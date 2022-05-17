#pragma once
#include "Graphics.h"
#include "GraphicDataTypes.h"

#include <DirectXMath.h>

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Entity
		{
		public:
			Entity() = default;
			~Entity() = default;
			virtual void Input();
			virtual void Update(float DeltaTime);
			virtual void Draw(MafiaBar::Engine::Graphics::Graphics& Graphics);
		public:
			constexpr MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> GetVertices() const;
			constexpr MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> GetIndices() const;
			constexpr DirectX::XMFLOAT3 GetLocation() const;
			constexpr DirectX::XMFLOAT3 GetRotation() const;
			constexpr DirectX::XMFLOAT3 GetScale() const;
			virtual DirectX::XMMATRIX GetTransformation() const;
		protected:
			MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> Vertices;
			MafiaBar::SDK::Vector<unsigned short> Indices;
			DirectX::XMFLOAT3 Location;
			DirectX::XMFLOAT3 Rotation;
			DirectX::XMFLOAT3 Scale;
		};


	}
}
