#pragma once
#include <array>

#include "Graphics.h"
#include "GraphicDataTypes.h"


namespace MafiaBar
{
	namespace Engine
	{
		class Entity
		{;
		public:
			Entity() = default;
			virtual void Input() {}
			virtual void Update(float Delta_Time) {}
			virtual void Draw(MafiaBar::Engine::Graphics::Graphics& Graphics) {}
			virtual DirectX::XMMATRIX GetTransformation() const { return DirectX::XMMATRIX(); }
		};
	}
}
