#include "pch.h"
#include "Window.h"
#include "App.h"
#pragma comment(lib, "Engine_Toolkit.lib")
#pragma comment(lib, "Discord.lib")
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	App app(hInstance);
	return 0;
}