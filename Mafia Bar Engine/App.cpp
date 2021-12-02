#include "pch.h"
#include "App.h"

App::App()
	: win("Mafia Bar Engine", 1200, 800)
{
}

int App::Go()
{
	while (true)
	{
		if (const auto ecode = win.ProcessMessages())
		{
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{

}
