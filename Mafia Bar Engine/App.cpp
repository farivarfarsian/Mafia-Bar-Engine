#include "pch.h"
#include "App.h"
App::App()
	: win("Mafia Bar Engine", 1200, 800, true)
{
	//Registering Mafia Bar Engine Default Hotkeys
	win.hotkey.RegisterHotKey(win.GetHandle(), win.hotkey.ESC, NULL, VK_ESCAPE);
	win.hotkey.RegisterHotKey(win.GetHandle(), win.hotkey.QUIT, MOD_CONTROL, 0x51);
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
	win.graphics->Clear(DirectX::Colors::Black, 1.0f, 0);
	win.graphics->TestRenderingTriangle(-time.Peek(), 0, 0);
	win.graphics->TestRenderingTriangle(time.Peek(), win.mouse.GetPosX() / 600.0f - 1.0f, -win.mouse.GetPosY() / 400.0f + 1.0f);
	win.graphics->EndFrame();
}
