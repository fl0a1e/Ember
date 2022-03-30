#pragma once

#include "Ember/Core.h"
#include "Ember/Events/Events.h" // 涉及事件处理（逐层下降传递消息）

namespace Ember {

	class EMBER_API Layer {
	public:

		Layer(const std::string& name = "Layer");

		virtual ~Layer();


		// attach layer to our app or the others
		virtual void onAttach() {}				

		// detach layer to our app or the others
		virtual void onDetach() {}				

		// 刷新指定 layer 
		virtual void onUpdate() {}				

		// 处理指定 layer 的事件
		virtual void onEvent(Event& event) {}	

		// 
		virtual void onImGuiRender() {}


		// 获取指定 layer 名称
		inline const std::string& getName() const { return layerDebugName; }	

	protected:
		std::string layerDebugName;
	};

}


