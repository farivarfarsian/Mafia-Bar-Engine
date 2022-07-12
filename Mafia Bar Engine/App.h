#pragma once
#include <Application.h>

class App final : public MafiaBar::Engine::Application
{
private:
	void Setup() override;
	void Frame() override;
};