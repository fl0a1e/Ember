#include "pch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Ember {

	Renderer::Renderer() {
		init();
	}

	Renderer::~Renderer() {
	
	}

	void Renderer::init() const {
		EMBER_CORE_INFO("OpenGL info:");
		EMBER_CORE_INFO("   Vendor: {0}", glGetString(GL_VENDOR));
		EMBER_CORE_INFO("   Renderer: {0}", glGetString(GL_RENDERER));
		EMBER_CORE_INFO("   Version {0}", glGetString(GL_VERSION));
	}

	void Renderer::refreshMainWindow() const {
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::draw(int style) const {

	}




}