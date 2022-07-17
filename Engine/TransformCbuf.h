#pragma once
#include "Bindable.h"
#include "ConstantBuffer.h"
#include "Entity.h"

#include "Engine.h" //Using the Scene instance.
#include "Transform.h" //Getting the TransformComponent of each entity.

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
							object.GetComponent<TransformComponent>()->GetTransform() * MafiaBar::Engine::Engine::Get().GetScene().GetSceneProjection()
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