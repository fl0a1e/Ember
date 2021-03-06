#pragma once

#include "pch.h"
#include "Ember/Window.h"

#include <GLFW/glfw3.h>

namespace Ember {

	class WindowsWindow : public Window {
	private:
		GLFWwindow* m_Window;	// GLFW的窗口对象

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;		// 窗口数据

	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();
		
		
		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		/// <summary>
		/// 垂直同步
		/// 设置当前 OpenGL context的交换间隔（从调用glfwSwapBuffers到交换缓冲区并返回之前等待的屏幕更新次数）
		/// </summary>
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;	// 是否开启垂直同步

		inline void* GetNativeWindow() const { return m_Window; };
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};


}

