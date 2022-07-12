#pragma once
#include "Component.h"
#include <utility>

namespace MafiaBar
{
	namespace Engine
	{
		struct MB_ENGINE_API TransformComponent final : public Component
		{
		public:
			TransformComponent operator+(const TransformComponent& TransformComponent);
			TransformComponent operator-(const TransformComponent& TransformComponent);
			TransformComponent operator*(const TransformComponent& TransformComponent);
			TransformComponent operator/(const TransformComponent& TransformComponent);
			TransformComponent();
			TransformComponent(const DirectX::XMFLOAT3& Position, const DirectX::XMFLOAT3& Scale, const DirectX::XMFLOAT3& Rotation);
			TransformComponent(DirectX::XMFLOAT3&& Position, DirectX::XMFLOAT3&& Scale, DirectX::XMFLOAT3&& Rotation);
			~TransformComponent();
			void SetPosition(float X, float Y, float Z);
			void SetScale(float X, float Y, float Z);
			void SetRotation(float X, float Y, float Z);
		public:
			DirectX::XMFLOAT3 GetPosition() const;
			DirectX::XMFLOAT3 GetScale() const;
			DirectX::XMFLOAT3 GetRotation() const;
			DirectX::XMMATRIX GetTransform() const;
			const char* GetName() const override;
		private:
			DirectX::XMFLOAT3 Position{ 0.0f, 0.0f, 0.0f };
			DirectX::XMFLOAT3 Scale{ 1.0f, 1.0f, 1.0f };
			DirectX::XMFLOAT3 Rotation{ 0.0f, 0.0f, 0.0f };
		};
	}
}
