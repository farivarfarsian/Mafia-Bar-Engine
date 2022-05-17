#pragma once
#include <Engine.h>
#include <Utilities.h>

#include "Cube.h"

class App final : public MafiaBar::Engine::Application
{
private:
	void Frame() override;
	void Setup() override;
	//Entities
	MafiaBar::SDK::Vector<Cube*> boxes;
	//Utilities
	MafiaBar::Utilities::Time Time;
};