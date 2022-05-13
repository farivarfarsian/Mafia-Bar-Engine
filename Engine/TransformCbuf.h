#pragma once
#include "Bindable.h"
#include "ConstantBuffer.h"
#include "Entity.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class TransformCbuf : public MafiaBar::Engine::Graphics::Bindable
			{
			public:
				TransformCbuf(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::Engine::Entity& object) : vertexconstantbuffer(graphics), object(object) {}
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override
				{
					vertexconstantbuffer.Update(graphics,
						DirectX::XMMatrixTranspose(
							object.GetTransformation() * graphics.GetProjection()
						)
					);
					vertexconstantbuffer.Bind(graphics);
				}
			private:
				MafiaBar::Engine::Graphics::VertexConstantBuffer<DirectX::XMMATRIX> vertexconstantbuffer;
				const MafiaBar::Engine::Entity& object;
			};
		}
	}
}