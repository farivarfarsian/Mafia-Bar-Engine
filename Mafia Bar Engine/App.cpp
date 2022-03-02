#include "App.h"

App::App()
	: win("Mafia Bar Engine", 1200, 800, false)
{
	DependencyFiles.AddDependencyFile("Assets/ConsoleFont.spritefont");
	DependencyFiles.Check();

	//Registering Mafia Bar Engine Default Hotkeys
	window->GetHotkey().RegisterHotKey(win.GetHandle(), win.GetHotkey().ESC, NULL, VK_ESCAPE);
	window->GetHotkey().RegisterHotKey(win.GetHandle(), win.GetHotkey().QUIT, MOD_CONTROL, Engine::Get().GetKeyboard().Q);
	window->GetHotkey().RegisterHotKey(win.GetHandle(), win.GetHotkey().FULLSCREEN, MOD_CONTROL, Engine::Get().GetKeyboard().F);

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 80; i++)
	{
		boxes.push_back(std::make_unique<Cube>(
			*Engine::Get().GetGraphics(), rng, adist,
			ddist, odist, rdist
			));
	}

	Engine::Get().GetGraphics()->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));

	Engine::Get().GetGraphics()->CreateSprite(L"Assets/ConsoleFont.spritefont");
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = win.ProcessMessages()) { return *ecode; }

		std::async(std::launch::async, &App::DoFrame, this);
	}
}

App::~App()
{
}

void App::DoFrame()
{
	Engine::Get().GetGraphics()->Clear(DirectX::Colors::Black, 1.0f, 0);

	const float delta_time = time.Mark();
	for (int i = 0; i < boxes.size(); i++)
	{
		boxes[i]->Update(delta_time);
		boxes[i]->Draw(*Engine::Get().GetGraphics());
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

	Engine::Get().GetGraphics()->EndFrame();
}
