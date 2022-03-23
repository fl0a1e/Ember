#include "pch.h"
#include "ImGUILayer.h"
#include "Ember/App.h"
#include "imgui.h"
#include "platform/OpenGL/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

namespace Ember {
	
	ImGUILayer::ImGUILayer()
		: Layer("ImGUILayer") {}

	ImGUILayer::~ImGUILayer() {
	}

	void ImGUILayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//io.KeyMap[] = 


		ImGui_ImplOpenGL3_Init("#version 410");
		
	}

	void ImGUILayer::onDetach() {
	}

	void ImGUILayer::onUpdate() {
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::get();
		io.DisplaySize = ImVec2(app.getWindow().GetWidth(), app.getWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = (time > 0.0f) ? (time - imGUILayer_time) : (1.0f / 60.0f);
		imGUILayer_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGUILayer::onEvent(Event& event) {
	}

}

