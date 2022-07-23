#include "App.h"
#include "Cube.h" //Cube Entity

void App::Setup()
{
	for (int i = 0; i < 200; i++)
	{
		MafiaBar::Engine::Engine::Get().GetScene().AddEntity(std::make_shared<Cube>());
	}
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
