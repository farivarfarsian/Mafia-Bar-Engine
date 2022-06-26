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
				/// <summary>
				///  Replaces the Passed VertexBuffer Instance with the already existing one, It replaces the VertexBuffer, Vertices, Offset and VertexBufferStride.
				///  Note: This Method needs Improvement for the third parameter, Perphaps VertexBuffer class could hold the Verticies in it in the future.
				/// </summary>
				template<typename VerticesType>
				void Replace(Graphics& Graphics, const VertexBuffer& VertexBuffer, const MafiaBar::SDK::Vector<VerticesType>& Vertices)
				{
					//Releasing the already existing data from the buffer.
					m_VertexBuffer->Release();

					//Copying VertexBuffer and getting its description.
					Microsoft::WRL::ComPtr<ID3D11Buffer> NewVertexBuffer = VertexBuffer.GetVertexBuffer();
					D3D11_BUFFER_DESC NewVertexBufferDECRIBTOR{};
					NewVertexBuffer->GetDesc(&NewVertexBufferDECRIBTOR);

					D3D11_SUBRESOURCE_DATA NewVertexSUBRESOURCE_DATA{};
					NewVertexSUBRESOURCE_DATA.pSysMem = Vertices.GetData();

					//Creating the new VertexBuffer
					DebugCode DEBUGCODE = Graphics.GetDevice()->CreateBuffer(&NewVertexBufferDECRIBTOR, &NewVertexSUBRESOURCE_DATA, m_VertexBuffer.GetAddressOf());

					//Copying the new created buffer into the VertexBuffer class buffer
					if (DEBUGCODE == S_OK)
					{
						m_VertexBuffer = NewVertexBuffer;
					}
					else
					{
						MB_EXCEPTION(DEBUGCODE);
					}

					//Copying other data from VertexBuffer and replacing them.
					this->VertexBufferStride = VertexBuffer.GetVertexBufferStride();
					this->Offset = VertexBuffer.GetVertexBufferOffset();
				}
			public:
				ID3D11Buffer* GetVertexBuffer() const;
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