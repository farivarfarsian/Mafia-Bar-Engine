#include "App.h"
#include "Cube.h" //Cube Entity

void App::Setup()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (int i = 0; i < 200; i++)
	{
		MafiaBar::Engine::Engine::Get().GetScene().AddEntity(std::make_shared<Cube>(MafiaBar::Engine::Engine::Get().GetGraphics(), rng, adist, ddist, odist, rdist));
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
