#include "pch.h"
#include "RenderWindow.h"
#include "../Engine Toolkit/System_Informations.h"
#include "../Discord/Discord.h"
#pragma comment(lib, "Engine_Toolkit.lib")
#pragma comment(lib, "Discord.lib")
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Discord::SetupDiscord();
	gInit = false;
	Discord::UpdateDiscord();
	Engine::Console::CreateConsole();
	Engine::Console::WelcomeMessage(USERNAME);
	std::cout << Engine::OS_Information::Window_Version();
	RenderWindow rw;
	rw.Initialize(hInstance, 1200, 800);
	rw.ProcessMessages();
	return 0;
}