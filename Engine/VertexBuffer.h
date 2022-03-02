#pragma once
#include "Bindable.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API VertexBuffer : public Bindable
			{
			public:
				template<typename VerticesType>
				VertexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::SDK::Vector<VerticesType>& vertices)
					: VertexBufferStride(sizeof(VerticesType))
				{
					D3D11_BUFFER_DESC VertexBufferDECRIBTOR = {};
					VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
					VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
					VertexBufferDECRIBTOR.MiscFlags = 0u;
					VertexBufferDECRIBTOR.ByteWidth = UINT(sizeof(VerticesType) * vertices.GetSize());
					VertexBufferDECRIBTOR.StructureByteStride = sizeof(VerticesType);
					D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
					VertexSUBRESOURCE_DATA.pSysMem = vertices.GetData();
					MB_EXCEPTION(graphics.GetDevice()->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &m_VertexBuffer));
				}
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