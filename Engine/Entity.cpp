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

constexpr DirectX::XMFLOAT3 MafiaBar::Engine::Entity::GetLocation() const
{
	return Location;
}

constexpr DirectX::XMFLOAT3 MafiaBar::Engine::Entity::GetRotation() const
{
	return Rotation;
}

constexpr DirectX::XMFLOAT3 MafiaBar::Engine::Entity::GetScale() const
{
	return Scale;
}


DirectX::XMMATRIX MafiaBar::Engine::Entity::GetTransformation() const
{
	return DirectX::XMMATRIX();
}