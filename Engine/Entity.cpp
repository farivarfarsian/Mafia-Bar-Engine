#include "Entity.h"

void MafiaBar::Engine::Entity::Input()
{

}

void MafiaBar::Engine::Entity::Update(float DeltaTime)
{

}

void MafiaBar::Engine::Entity::Draw(MafiaBar::Engine::Graphics::Graphics& Graphics)
{

}

DirectX::XMMATRIX MafiaBar::Engine::Entity::GetTransformation() const
{
	return DirectX::XMMATRIX();
}

MafiaBar::SDK::Vector<void*> MafiaBar::Engine::Entity::GetComponents() const
{
	return Components;
}

EntityID MafiaBar::Engine::Entity::GetEntityID() const
{
	return EntityID;
}
