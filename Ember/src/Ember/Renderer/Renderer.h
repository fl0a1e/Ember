#pragma once
#include "pch.h"

#include "Ember/Renderer/Shader.h"

namespace Ember {

	class EMBER_API Renderer {
	public:
		Renderer();
		~Renderer();

		void init() const ;

		/// <summary>
		/// ˢ�´��ڣ���ֹ��β
		/// </summary>
		void refreshMainWindow() const ;


	public:
		
		

	public:
		/// <summary>
		/// ������Ⱦ��ʽ��ִ����Ⱦ
		/// @style: ��Ⱦ��ʽ
		/// 
		/// </summary>
		/// <param name="style"></param>
		void draw(int style) const ;

		
	};
}

