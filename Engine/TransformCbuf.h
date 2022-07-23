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
				TransformCbuf(Entity* Entity) : vertexconstantbuffer(), Entity(Entity) {}
				void Bind() override
				{
					vertexconstantbuffer.Update(
						DirectX::XMMatrixTranspose(
							Entity->GetComponent<TransformComponent>()->GetTransform() * MafiaBar::Engine::Engine::Get().GetScene().GetSceneProjection()
						)
					);
					vertexconstantbuffer.Bind();			
				}
			private:
				MafiaBar::Engine::Graphics::VertexConstantBuffer<DirectX::XMMATRIX> vertexconstantbuffer;
				MafiaBar::Engine::Entity* Entity;
			};
		}
	}
}