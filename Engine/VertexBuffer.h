#pragma once
#include "Bindable.h"
#include "GraphicDataTypes.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API VertexBuffer : public Bindable
			{
			public:
				VertexBuffer(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices);
				VertexBuffer(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices);
				void Bind() override;
				/// <summary>
				///  Replaces the Passed VertexBuffer Instance with the already existing one, It replaces the VertexBuffer, Vertices, Offset and VertexBufferStride.
				/// </summary>
				void Replace(const VertexBuffer& VertexBuffer);
			public:
				ID3D11Buffer* GetVertexBuffer() const;
				unsigned int GetVertexBufferStride() const;
				unsigned int GetVertexBufferOffset() const;
				std::vector<MafiaBar::Graphics::Vertex> GetVertices() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11Buffer> m_VertexBuffer;
				unsigned int VertexBufferStride;
				unsigned int Offset = 0u;
			};
		}
	}
}