#include "App.h"
LINK_LIBRARY("Engine.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	App Application;

	Application.Initialize("Mafia Bar Engine", "Mafia Bar", 1200, 800, false, 106, 103);

	Application.Present();

	MafiaBar::Engine::Engine::Get().Shutdown(); //The "Engine" Singleton for some reason isn't releasing itself and its objects, So we have to do it manually. PLEASE FIX THIS

	return App::MB_SYS_CODES::SUCCEEDED;
}