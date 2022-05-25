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
		/// 刷新窗口，防止拖尾
		/// </summary>
		void refreshMainWindow() const ;


	public:
		
		

	public:
		/// <summary>
		/// 设置渲染方式和执行渲染
		/// @style: 渲染方式
		/// 
		/// </summary>
		/// <param name="style"></param>
		void draw(int style) const ;

		
	};
}

