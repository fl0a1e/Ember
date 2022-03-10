#pragma once

#include "pch.h"

#include "Core.h"
#include "Events/Events.h"


namespace Ember {

	struct WindowProps{
		std::string Title;
		unsigned int Height;
		unsigned int Width;

		WindowProps(const std::string& _title = "Ember Renderer",
					unsigned int _height = 720,
					unsigned int _width = 1280)
			: Title(_title), Height(_height), Width(_width)
		{}
	};

	// Interface (to be fulfill for each platform)
	class EMBER_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;	// 定义回调函数类

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;	// 接受一个回调函数类的指针（引用）
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}