#include "pch.h"
#include "App.h"
App::App()
	: win("Mafia Bar Engine", 1200, 800)
{
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = win.ProcessMessages()) { return *ecode; }
		DoFrame();
	}
}

void App::DoFrame()
{
	int MouseX = 0, MouseY = 0;
	win.graphics->Clear(DirectX::Colors::Black, 1.0f, 0);
	win.graphics->TestRenderingTriangle(time.Peek(), MouseX / 1200.0f /*win.mouse.GetPosX() / 1200.0f*/, MouseY / 800.0f /*win.mouse.GetPosY() / 1200.0f*/);
	win.graphics->EndFrame();
}
