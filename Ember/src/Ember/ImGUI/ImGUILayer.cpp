#include "pch.h"
#include "Ember/Core.h"
#include "ImGUILayer.h"
#include "Ember/App.h"
#include "imgui.h"
#include "platform/OpenGL/imgui_impl_opengl3.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ember {
	
	ImGUILayer::ImGUILayer()
		: Layer("ImGUILayer") {}

	ImGUILayer::~ImGUILayer() {
	}

	void ImGUILayer::onAttach() {
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
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

	void ImGUILayer::onEvent(Event& e) {
		// 事件调度器
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FN(ImGUILayer::onMouseButtonPressed));
		dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FN(ImGUILayer::onMouseButtonReleased));
		dispatcher.dispatch<MouseScrolled>(BIND_EVENT_FN(ImGUILayer::onMouseScrolled));
		dispatcher.dispatch<MouseMoved>(BIND_EVENT_FN(ImGUILayer::onMouseMoved));
		dispatcher.dispatch<KeyPressed>(BIND_EVENT_FN(ImGUILayer::onKeyPressed));
		dispatcher.dispatch<KeyReleased>(BIND_EVENT_FN(ImGUILayer::onKeyReleased));
		//dispatcher.dispatch<KeyTyped>(BIND_EVENT_FN(ImGUILayer::onKeyTyped));
		dispatcher.dispatch<WindowResize>(BIND_EVENT_FN(ImGUILayer::onWindowResize));
		
	}

	bool ImGUILayer::onMouseButtonPressed(MouseButtonPressed& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = true;

		return false;
	}

	bool ImGUILayer::onMouseButtonReleased(MouseButtonReleased& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = false;

		return false;
	}

	bool ImGUILayer::onMouseScrolled(MouseScrolled& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.getOffsetX();
		io.MouseWheel += e.getOffsetY();

		return false;
	}

	bool ImGUILayer::onMouseMoved(MouseMoved& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.getX(), e.getY());

		return false;
	}

	bool ImGUILayer::onKeyPressed(KeyPressed& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		return false;
	}

	bool ImGUILayer::onKeyReleased(KeyReleased& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = false;

		return false;
	}

	/*bool ImGUILayer::onKeyTyped(KeyTyped& e)
	{
		return false;
	}*/

	bool ImGUILayer::onWindowResize(WindowResize& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0 , 0, e.getWidth(), e.getHeight());

		return false;
	}

}

