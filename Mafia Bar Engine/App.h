#pragma once
#include "Window.h"
class App
{
public:
	App();
	int Go();
	~App();
private:
	void DoFrame();
	Window win;
	MafiaBar::Time time;
};