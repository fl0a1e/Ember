#pragma once

#include "Ember/Core.h"
#include "Ember/Events/Events.h" // �漰�¼���������½�������Ϣ��

namespace Ember {

	class EMBER_API Layer {
	public:

		Layer(const std::string& name = "Layer");

		virtual ~Layer();


		// attach layer to our app or the others
		virtual void onAttach() {}				

		// detach layer to our app or the others
		virtual void onDetach() {}				

		// ˢ��ָ�� layer 
		virtual void onUpdate() {}				

		// ����ָ�� layer ���¼�
		virtual void onEvent(Event& event) {}	

		// 
		virtual void onImGuiRender() {}


		// ��ȡָ�� layer ����
		inline const std::string& getName() const { return layerDebugName; }	

	protected:
		std::string layerDebugName;
	};

}


