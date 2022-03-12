#include "pch.h"
#include "platform/Windows/WindowsWindow.h"
#include "Ember/Events/AppEvents.h"
#include "Ember/Events/KeyEvents.h"
#include "Ember/Events/MouseEvents.h"

#include "glad/glad.h"


namespace Ember {

	static bool s_GLFWWindowCount = false;


	static void GLFWErrorCallback(int error_code, const char* description) {
		EMBER_CORE_ERR("GLFW err: {0} {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		EMBER_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWWindowCount)
		{
			
			int success = glfwInit();
			EMBER_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWWindowCount = true;
			
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);	// glad: load all OpenGL function pointers
		EMBER_CORE_ASSERT(status, "Failed to initialize Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// set GLFW callbacks
		// use lambda
		// ------------------------------------------------------------

		// �رմ���
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowClose event;
			data.EventCallback(event);
		});

		// ���ڴ�С
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	// ��ȡ��ǰ��������

			// ����
			data.Width = width;
			data.Height = height;

			WindowResize event(width, height);	// �����¼�
			data.EventCallback(event);
		});

		// ����
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	// ��ȡ��ǰ��������
			
			switch (action) {

				case GLFW_PRESS: {
					KeyPressed event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleased event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressed event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		/*
		// ��갴��
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {

				case GLFW_PRESS: {
					MouseBu event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleased event(key);
					data.EventCallback(event);
					break;
				}
			}
		});
		*/


		// ����
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolled event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		// ����ƶ�
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoved event((float)xpos, (float)ypos);
			data.EventCallback(event);
		});
	}


	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}


	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);	// Ҳ�д�ֱͬ�������õ�ǰ OpenGL context�Ľ���������ӵ���glfwSwapBuffers������������������֮ǰ�ȴ�����Ļ���´�����
		}
		else {
			glfwSwapInterval(0);
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}
}