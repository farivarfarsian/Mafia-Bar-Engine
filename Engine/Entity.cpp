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
		static_cast<MafiaBar::Engine::Component*>(Component)->Run();
	}
}

MafiaBar::SDK::Vector<void*> MafiaBar::Engine::Entity::GetComponents() const
{
	return Components;
}

EntityID MafiaBar::Engine::Entity::GetEntityID() const
{
	return EntityID;
}
