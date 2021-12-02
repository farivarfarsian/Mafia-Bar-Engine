#pragma once
#include "Window.h"
#include <MB_Utils.h>
class App
{
public:
	App();
	int Go();
private:
	void DoFrame();
	Window win;
	MafiaBar::Console console;
};