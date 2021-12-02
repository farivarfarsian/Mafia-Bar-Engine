#include "pch.h"
#include "App.h"
#pragma comment(lib, "Engine.lib")
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	App app;
	app.Go();
	return 0;
}