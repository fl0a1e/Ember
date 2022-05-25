#include "pch.h"
#include "Ember/App.h"
#include "Events/AppEvents.h"
#include "Ember/LayerStack.h"

#include "glad/glad.h"

namespace Ember {
	
	App* App::s_Instance = nullptr;

	App::App() {
		EMBER_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		// ���ô��ڻص�������glfwSet...Callback �¼���������� data.
		// �� SetEventCallback ����Ϊ onEvent()
		// onEvent() ͨ��std::bind �󶨵�ռλ���Ĳ�������Event& e��
		// �Ӷ����ݲ�ͬ�¼����� �¼������� EventDispatcher ������庯��
		// �Ⱦۺ��ٷ��䣬�����·���ã���·�ֽ�
		m_Window->SetEventCallback(BIND_EVENT_FN(App::onEvent));

		m_imGuiLayer = new ImGUILayer();
		pushOverlay(m_imGuiLayer);

		// ----------------------------------------
		renderer = new Renderer();

		std::string vertexSrc = R"(
        #version 330 core

        layout (location = 0) in vec3 aPos;
		
        void main()
        {  
			gl_Position = vec4(aPos, 1.0f);
        }
		)";

		std::string fragmentSrc = R"(
		#version 330 core
		out vec4 FragColor;
		
		void main()
		{
			FragColor = vec4(1.f, 0.f, 0.f, 1.0f);
		}
		)";

	
		// ------------triangle--------------------
		
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f, // left  
			 0.5f, -0.5f, 0.0f, // right 
			 0.0f,  0.5f, 0.0f  // top   
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

		GLuint indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

		sha.reset(new Shader(vertexSrc, fragmentSrc));
	}

	App::~App() {
	}

	void App::pushLayer(Layer* layer) {
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void App::pushOverlay(Layer* overlay) {
		layerStack.pushOverlay(overlay);
		overlay->onAttach();
	}

	void App::onEvent(Event& e) {
		// �¼�������
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowClose>(BIND_EVENT_FN(App::onWindowClose));

		// ����¼���Ϣ
		EMBER_CORE_TRACE("{0}", e);

		// ���϶��´����¼���Ϣ
		for (auto it = layerStack.end(); it != layerStack.begin(); ) {
			(*--it)->onEvent(e);
			if (e.isHandled) {
				break;
			}
		}
	}

	void App::Run() {

		// main loop
		while (isRunning) {
			
			renderer->refreshMainWindow();

			sha->bind();
			glBindVertexArray(vertexArray);
			
			// ������Ⱦ��ʽ�������棩
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			//glDrawArrays(GL_TRIANGLES, 0, 3);
			
			// ����ÿ�� layer
			for (Layer* layer : layerStack) {
				layer->onUpdate();
			}

			m_imGuiLayer->Begin();
			for (Layer* layer : layerStack) {
				layer->onImGuiRender();
			}
			m_imGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}


	bool App::onWindowClose(WindowClose& e) {
		isRunning = false;
		return true;
	}

}
