#include "App.h"

void App::BeforeFrame()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (int i = 0; i < 200; i++)
	{
		boxes.PushBack(new Cube(*MafiaBar::Engine::Engine::Get().GetGraphics(), rng, adist, ddist, odist, rdist));
	}

	MafiaBar::Engine::Engine::Get().GetGraphics()->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

void App::Frame()
{
	MafiaBar::Engine::Engine::Get().GetGraphics()->Clear(DirectX::Colors::Black, 1.0f, 0);

	const float delta_time = Time.Mark();
	for (int i = 0; i < boxes.GetSize(); i++)
	{
		boxes[i]->Update(delta_time);
		boxes[i]->Draw(*MafiaBar::Engine::Engine::Get().GetGraphics());
	}

	/*
	win.GetGraphics().GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred,m_States->NonPremultiplied()); //Fix the ID3D11BlendState, DirectX::CommonStates NonPremultiplied() would be helpful.
	win.GetGraphics().GetSpriteFont()->DrawString(
		win.GetGraphics().GetSpriteBatch(),
		"Hello World",
		DirectX::XMFLOAT2(0, 0),
		DirectX::Colors::White, 0.0f,
		DirectX::XMFLOAT2(0, 0),
		DirectX::XMFLOAT2(1.0f, 1.0f));
	win.GetGraphics().GetSpriteBatch()->End();
	*/

	MafiaBar::Engine::Engine::Get().GetGraphics()->EndFrame();
}
