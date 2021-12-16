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
	//const float c = sin(time.Peek()) / 2.0f + 0.5f;
	time.Start("Rendering Rainbowed Triangle");
	win.graphics->ClearRenderBufferColor(0.0f, 0.0f, 0.0f, 1.0f);
	win.graphics->DrawRainbowedTrinagle();
	win.graphics->EndFrame();
	time.End();
}
