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

		// 关闭窗口
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowClose event;
			data.EventCallback(event);
		});

		// 窗口大小
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	// 获取当前窗口数据

			// 更新
			data.Width = width;
			data.Height = height;

			WindowResize event(width, height);	// 创建事件
			data.EventCallback(event);
		});

		// 按键
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);	// 获取当前窗口数据
			
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
		// 鼠标按键
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


		// 滚轮
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolled event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		// 鼠标移动
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
			glfwSwapInterval(1);	// 也叫垂直同步，设置当前 OpenGL context的交换间隔（从调用glfwSwapBuffers到交换缓冲区并返回之前等待的屏幕更新次数）
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