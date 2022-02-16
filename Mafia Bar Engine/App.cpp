#include "App.h"

App::App()
	: win("Mafia Bar Engine", 1200, 800, false)
{
	//Registering Mafia Bar Engine Default Hotkeys
	win.GetHotkey().RegisterHotKey(win.GetHandle(), win.GetHotkey().ESC, NULL, VK_ESCAPE);
	win.GetHotkey().RegisterHotKey(win.GetHandle(), win.GetHotkey().QUIT, MOD_CONTROL, win.GetKeyboard().Q);
	win.GetHotkey().RegisterHotKey(win.GetHandle(), win.GetHotkey().FULLSCREEN, MOD_CONTROL, win.GetKeyboard().F);

	
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

	win.GetGraphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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
	win.GetGraphics().Clear(DirectX::Colors::Black, 1.0f, 0);
	const float delta_time = time.Mark();
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->Update(delta_time);
		boxes[i]->Draw(win.GetGraphics());
	}
	win.GetGraphics().EndFrame();
}
