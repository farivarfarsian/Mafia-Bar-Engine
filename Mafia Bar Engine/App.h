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
	Window win;
	MafiaBar::Time time;
	std::vector<std::unique_ptr<Cube>> boxes;
};