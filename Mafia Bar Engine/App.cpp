#include "pch.h"
#include "App.h"

App::App()
	: win("Mafia Bar Engine", 1200, 800)
{
	Engine::Console::CreateConsole();
	Engine::Console::WelcomeMessage(USERNAME);
}

int App::Go()
{
	MSG msg;
	BOOL gResult;
	while ( (gResult = GetMessage(&msg, nullptr, 0, 0)) > 0 )
	{
		TranslateMessage(&msg);

		DispatchMessage(&msg);

		DoFrame();
	}

	if (gResult == -1) { throw MB_LAST_EXCEPTION; }

	return msg.wParam;
}

void App::DoFrame()
{

}
