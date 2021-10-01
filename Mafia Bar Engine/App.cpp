#include "pch.h"
#include "App.h"

App::App(HINSTANCE hInstance)
	: win(hInstance, "Mafia Bar Engine", 1200, 800)
{
	Engine::Console::CreateConsole();
	Engine::Console::WelcomeMessage(USERNAME);
	SetupDiscord();
	win.ProcessMessages();
}

int App::Go()
{
	return 0;
}

void App::SetupDiscord()
{
	Discord::SetupDiscord();
	gInit = false;
	Discord::UpdateDiscord();
}

void App::DoFrame()
{
}
