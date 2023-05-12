#include "App.h"
#include "Cube.h" //Cube Entity
#include <Utilities.h>
#include <iostream>

void App::Setup()
{
	MafiaBar::Engine::Engine::Get().GetScene().AddEntity(std::make_shared<Cube>());
}

void App::Frame()
{
	{
		ImGui::Begin("Test Window");
		ImGui::Button("HelloWorld");
		ImGui::Text("Frame (%.1f FPS)", ImGui::GetIO().Framerate);
		ImGui::End();
	}
}
