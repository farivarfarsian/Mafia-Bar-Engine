#pragma once
#include "Window.h"

#include <Cube.h>

#include <DependencyFiles.h>

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
	std::vector<std::unique_ptr<Cube>> boxes;
	MafiaBar::Engine::DependencyFiles DependencyFiles;
};