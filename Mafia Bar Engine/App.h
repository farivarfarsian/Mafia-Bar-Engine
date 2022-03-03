#pragma once
#include "Window.h"

#include <Cube.h>

class App
{
public:
	App();
	int Go();
	~App();

private:
	void DoFrame();
	MafiaBar::Time time;
	Window win;
	MafiaBar::SDK::Vector<Cube*> boxes;
};