#pragma once
#include "Engine.h"
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE VertexBuffer : public Bindable
			{
			public:
				VertexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, MafiaBar::Graphics::Vertex* vertices);
				VertexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& vertices) {};
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override;
			public:
				unsigned int GetVertexBufferStride() const;
				unsigned int GetVertexBufferOffset() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
				unsigned int VertexBufferStride;
				unsigned int Offset = 0u;
			};
		}
	}
}