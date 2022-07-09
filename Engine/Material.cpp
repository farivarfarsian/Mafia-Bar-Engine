#include "Material.h"

void MafiaBar::Engine::Material::Initialize(const DirectX::XMFLOAT4& Color)
{
	this->Color.x = Color.x;
	this->Color.y = Color.y;
	this->Color.z = Color.z;
}

void MafiaBar::Engine::Material::Initialize(const char* TexturePath, const DirectX::XMFLOAT2& TextureCordinates)
{
	this->TexturePath = TexturePath;
	this->TextureCordinates.x = TextureCordinates.x;
	this->TextureCordinates.y = TextureCordinates.y;
}

DirectX::XMFLOAT4 MafiaBar::Engine::Material::GetColor() const
{
	return Color;
}

DirectX::XMFLOAT2 MafiaBar::Engine::Material::GetTextureCordinates() const
{
	return TextureCordinates;
}

const char* MafiaBar::Engine::Material::GetTexturePath() const
{
	return TexturePath;
}
