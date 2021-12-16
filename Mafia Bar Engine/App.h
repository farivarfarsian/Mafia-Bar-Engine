#pragma once
#include "Window.h"
#include <Engine.h>
class App
{
public:
	App();
	int Go();
private:
	void DoFrame();
	Window win;
	MafiaBar::Console console;
	MafiaBar::Time time;
};