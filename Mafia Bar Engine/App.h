#pragma once
#include "Window.h"
#include <System_Informations.h>
#include "../Discord/Discord.h"
class App
{
public:
	App() = default;
	App(HINSTANCE hInstance);
	int Go();
public:
	void SetupDiscord();
private:
	void DoFrame();
private:
	Window win;
};