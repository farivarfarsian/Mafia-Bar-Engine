#include "Transform.h"

MafiaBar::Engine::TransformComponent MafiaBar::Engine::TransformComponent::operator+(const TransformComponent& TransformComponent)
{
	MafiaBar::Engine::TransformComponent Transform;

	Transform.Position.x = this->Position.x + TransformComponent.GetPosition().x;
	Transform.Position.y = this->Position.y + TransformComponent.GetPosition().y;
	Transform.Position.z = this->Position.z + TransformComponent.GetPosition().z;

	Transform.Scale.x = this->Scale.x + TransformComponent.GetScale().x;
	Transform.Scale.y = this->Scale.y + TransformComponent.GetScale().y;
	Transform.Scale.z = this->Scale.z + TransformComponent.GetScale().z;

	Transform.Rotation.x = this->Rotation.x + TransformComponent.GetRotation().x;
	Transform.Rotation.y = this->Rotation.y + TransformComponent.GetRotation().y;
	Transform.Rotation.z = this->Rotation.z + TransformComponent.GetRotation().z;

	return Transform;
}

MafiaBar::Engine::TransformComponent MafiaBar::Engine::TransformComponent::operator-(const TransformComponent& TransformComponent)
{
	MafiaBar::Engine::TransformComponent Transform;

	Transform.Position.x = this->Position.x - TransformComponent.GetPosition().x;
	Transform.Position.y = this->Position.y - TransformComponent.GetPosition().y;
	Transform.Position.z = this->Position.z - TransformComponent.GetPosition().z;

	Transform.Scale.x = this->Scale.x - TransformComponent.GetScale().x;
	Transform.Scale.y = this->Scale.y - TransformComponent.GetScale().y;
	Transform.Scale.z = this->Scale.z - TransformComponent.GetScale().z;

	Transform.Rotation.x = this->Rotation.x - TransformComponent.GetRotation().x;
	Transform.Rotation.y = this->Rotation.y - TransformComponent.GetRotation().y;
	Transform.Rotation.z = this->Rotation.z - TransformComponent.GetRotation().z;

	return Transform;
}

MafiaBar::Engine::TransformComponent MafiaBar::Engine::TransformComponent::operator*(const TransformComponent& TransformComponent)
{
	MafiaBar::Engine::TransformComponent Transform;

	Transform.Position.x = this->Position.x * TransformComponent.GetPosition().x;
	Transform.Position.y = this->Position.y * TransformComponent.GetPosition().y;
	Transform.Position.z = this->Position.z * TransformComponent.GetPosition().z;

	Transform.Scale.x = this->Scale.x * TransformComponent.GetScale().x;
	Transform.Scale.y = this->Scale.y * TransformComponent.GetScale().y;
	Transform.Scale.z = this->Scale.z * TransformComponent.GetScale().z;

	Transform.Rotation.x = this->Rotation.x * TransformComponent.GetRotation().x;
	Transform.Rotation.y = this->Rotation.y * TransformComponent.GetRotation().y;
	Transform.Rotation.z = this->Rotation.z * TransformComponent.GetRotation().z;

	return Transform;
}

MafiaBar::Engine::TransformComponent MafiaBar::Engine::TransformComponent::operator/(const TransformComponent& TransformComponent)
{
	MafiaBar::Engine::TransformComponent Transform;

	Transform.Position.x = this->Position.x / TransformComponent.GetPosition().x;
	Transform.Position.y = this->Position.y / TransformComponent.GetPosition().y;
	Transform.Position.z = this->Position.z / TransformComponent.GetPosition().z;

	Transform.Scale.x = this->Scale.x / TransformComponent.GetScale().x;
	Transform.Scale.y = this->Scale.y / TransformComponent.GetScale().y;
	Transform.Scale.z = this->Scale.z / TransformComponent.GetScale().z;

	Transform.Rotation.x = this->Rotation.x / TransformComponent.GetRotation().x;
	Transform.Rotation.y = this->Rotation.y / TransformComponent.GetRotation().y;
	Transform.Rotation.z = this->Rotation.z / TransformComponent.GetRotation().z;

	return Transform;
}

MafiaBar::Engine::TransformComponent::TransformComponent()
{

}

MafiaBar::Engine::TransformComponent::TransformComponent(const DirectX::XMFLOAT3& Position, const DirectX::XMFLOAT3& Scale, const DirectX::XMFLOAT3& Rotation)
	: Position(Position), Scale(Scale), Rotation(Rotation)
{

}

MafiaBar::Engine::TransformComponent::TransformComponent(DirectX::XMFLOAT3&& Position, DirectX::XMFLOAT3&& Scale, DirectX::XMFLOAT3&& Rotation)
	: Position(std::move(Position)), Scale(std::move(Scale)), Rotation(std::move(Rotation))
{

}

MafiaBar::Engine::TransformComponent::~TransformComponent()
{

}

void MafiaBar::Engine::TransformComponent::SetPosition(float X, float Y, float Z)
{
	Position.x = X;
	Position.y = Y;
	Position.z = Z;
}

void MafiaBar::Engine::TransformComponent::SetScale(float X, float Y, float Z)
{
	Scale.x = X;
	Scale.y = Y;
	Scale.z = Z;
}


void MafiaBar::Engine::TransformComponent::SetRotation(float X, float Y, float Z)
{
	Rotation.x = X;
	Rotation.y = Y;
	Rotation.z = Z;
}

DirectX::XMFLOAT3 MafiaBar::Engine::TransformComponent::GetPosition() const
{
	return Position;
}

DirectX::XMFLOAT3 MafiaBar::Engine::TransformComponent::GetScale() const
{
	return Scale;
}

DirectX::XMFLOAT3 MafiaBar::Engine::TransformComponent::GetRotation() const
{
	return Rotation;
}

const char* MafiaBar::Engine::TransformComponent::GetName() const
{
	return "Transform";
}
