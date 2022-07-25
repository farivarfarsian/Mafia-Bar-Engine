#include "Entity.h"

void MafiaBar::Engine::Entity::Input()
{

}

void MafiaBar::Engine::Entity::Update(float DeltaTime)
{

}

void MafiaBar::Engine::Entity::Draw(Graphics::Graphics& Graphics)
{
	for (auto& Component : Components)
	{
		Component->Run();
	}
}

MafiaBar::SDK::Vector<std::shared_ptr<MafiaBar::Engine::Component>> MafiaBar::Engine::Entity::GetComponents() const
{
	return Components;
}

EntityID MafiaBar::Engine::Entity::GetEntityID() const
{
	return EntityID;
}
