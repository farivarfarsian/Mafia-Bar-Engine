#pragma once
#include "def.h"
#include "pch.h"

#include "Component.h"

namespace MafiaBar
{
	namespace Engine
	{
		struct MB_ENGINE_API Material
		{
		public:
			Material() = default;
			void Initialize(const DirectX::XMFLOAT4& Color);
			void Initialize(const char* TexturePath, const DirectX::XMFLOAT2& TextureCordinates);
		public:
			DirectX::XMFLOAT4 GetColor() const;
			DirectX::XMFLOAT2 GetTextureCordinates() const;
			const char* GetTexturePath() const;
		private:
			DirectX::XMFLOAT4 Color{ 0.0f, 0.0f ,0.0f ,1.0f };
			DirectX::XMFLOAT2 TextureCordinates{ 0.0f, 0.0f };
			const char* TexturePath = nullptr;
		}; //The structure is absolutely incomplete, Needs a lot more implementations and improvements will get to them when implementing the Assimp library.
	}
}