#pragma once

#include "pch.h"
#include "Ember/Window.h"

#include <GLFW/glfw3.h>

namespace Ember {

	class WindowsWindow : public Window {
	private:
		GLFWwindow* m_Window;	// GLFW�Ĵ��ڶ���

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;		// ��������

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override; // ��ֱͬ��
		bool IsVSync() const override;	// �Ƿ�����ֱͬ��

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};


}

