#include "App.h"

void App::Setup()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (int i = 0; i < 200; i++)
	{
		boxes.PushBack(new Cube(MafiaBar::Engine::Engine::Get().GetGraphics(), rng, adist, ddist, odist, rdist));
	}

	MafiaBar::Engine::Engine::Get().GetScene().SetSceneProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::Frame()
{
	MafiaBar::Engine::Engine::Get().GetScene().Clear(DirectX::Colors::Black, 1.0f, 0);

	const float delta_time = Time.Mark();
	for (int i = 0; i < boxes.GetSize(); i++)
	{
		boxes[i]->Input();
		boxes[i]->Update(delta_time);
		boxes[i]->Draw(MafiaBar::Engine::Engine::Get().GetGraphics());
	}

	MafiaBar::Engine::Engine::Get().GetScene().Render();
}
