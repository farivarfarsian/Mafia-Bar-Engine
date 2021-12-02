#pragma once
#include "Window.h"
#include <System_Informations.h>
class App
{
public:
	App();
	int Go();
private:
	void DoFrame();
private:
	Window win;
};