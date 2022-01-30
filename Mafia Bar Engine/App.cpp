#include "App.h"

App::App()
	: win("Mafia Bar Engine", 1200, 800, false)
{
	//Registering Mafia Bar Engine Default Hotkeys
	win.hotkey.RegisterHotKey(win.GetHandle(), win.hotkey.ESC, NULL, VK_ESCAPE);
	win.hotkey.RegisterHotKey(win.GetHandle(), win.hotkey.QUIT, MOD_CONTROL, win.keyboard.Q);
	win.hotkey.RegisterHotKey(win.GetHandle(), win.hotkey.FULLSCREEN, MOD_CONTROL, win.keyboard.F);

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Cube>(
			win.GetGraphics(), rng, adist,
			ddist, odist, rdist
			));
	}
	win.graphics->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = win.ProcessMessages()) { return *ecode; }
		DoFrame();
	}
}

App::~App()
{
}

void App::DoFrame()
{
	float delta_time = time.Mark();
	win.graphics->Clear(DirectX::Colors::Black, 1.0f, 0);
	for (auto& b : boxes)
	{
		b->Update(delta_time);
		b->Draw(win.GetGraphics());
	}
	//win.graphics->TestRenderingTriangle(-time.Peek(), 0, 0);
	//win.graphics->TestRenderingTriangle(time.Peek(), win.mouse.GetPosX() / 600.0f - 1.0f, -win.mouse.GetPosY() / 400.0f + 1.0f);
	win.graphics->EndFrame();
}
