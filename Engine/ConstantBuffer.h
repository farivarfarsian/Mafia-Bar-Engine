#pragma once
#include "Bindable.h"

//Note: You can't export Template Method/Constructors From a DLL. So Everything should be in the header file.

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			template <class ConstantTemplateType>
			class ConstantBuffer : public Bindable
			{
			public:
				ConstantBuffer(const ConstantTemplateType& ConstantType)
				{
					D3D11_BUFFER_DESC ConstantBufferDECRIBTOR = {};
					ConstantBufferDECRIBTOR.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
					ConstantBufferDECRIBTOR.Usage = D3D11_USAGE_DYNAMIC;
					ConstantBufferDECRIBTOR.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					ConstantBufferDECRIBTOR.MiscFlags = 0u;
					ConstantBufferDECRIBTOR.ByteWidth = sizeof(ConstantType);
					ConstantBufferDECRIBTOR.StructureByteStride = 0u;
					D3D11_SUBRESOURCE_DATA ConstantSUBRESOURCE_DATA{};
					ConstantSUBRESOURCE_DATA.pSysMem = &ConstantType;
					MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&ConstantBufferDECRIBTOR, &ConstantSUBRESOURCE_DATA, &mConstantBuffer));
				}
				ConstantBuffer()
				{
					D3D11_BUFFER_DESC ConstantBufferDECRIBTOR = {};
					ConstantBufferDECRIBTOR.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
					ConstantBufferDECRIBTOR.Usage = D3D11_USAGE_DYNAMIC;
					ConstantBufferDECRIBTOR.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					ConstantBufferDECRIBTOR.MiscFlags = 0u;
					ConstantBufferDECRIBTOR.ByteWidth = sizeof(ConstantTemplateType);
					ConstantBufferDECRIBTOR.StructureByteStride = 0u;
					MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&ConstantBufferDECRIBTOR, nullptr, &mConstantBuffer));
				}
				void Update(const ConstantTemplateType& ConstantType)
				{
					D3D11_MAPPED_SUBRESOURCE MappedSubSource;
					MB_EXCEPTION(Graphics->GetContext()->Map(mConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &MappedSubSource));
					memcpy(MappedSubSource.pData, &ConstantType, sizeof(ConstantType));
					Graphics->GetContext()->Unmap(mConstantBuffer.Get(), 0u);
				}
			protected:
				Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;
			};

			template <class VertexConstantTemplateType>
			class VertexConstantBuffer : public ConstantBuffer<VertexConstantTemplateType>
			{
				using ConstantBuffer<VertexConstantTemplateType>::mConstantBuffer; //Using mConstantBuffer Variable From ConstantBuffer Class
			public:
				using ConstantBuffer<VertexConstantTemplateType>::ConstantBuffer; //Using ConstantBuffer Constructor
				void Bind() override { this->Graphics->GetContext()->VSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf()); }
				/// <summary>
				/// Replace the old VertexConstantBuffer with the new one that user specifies.
				/// Note: This Method needs Improvement for the third parameter, Perphaps VertexConstantBuffer class could hold the passed VertexConstantBuffer onto the Memomry in the future.
				/// </summary>
				void Replace(const VertexConstantBuffer& VertexConstantBuffer, const VertexConstantTemplateType& VertexConstant)
				{
					//Releasing the already existing data in the buffer.
					mConstantBuffer->Release();

					//Copying the new buffer and getting its description.
					Microsoft::WRL::ComPtr<ID3D11Buffer> NewVertexConstantBuffer = VertexConstantBuffer.GetVertexConstantBuffer();
					D3D11_BUFFER_DESC NewVertexConstantBufferDESC{};
					NewVertexConstantBuffer.Get()->GetDesc(&NewVertexConstantBufferDESC);
					D3D11_SUBRESOURCE_DATA NewVertexConstantBufferData{};
					NewVertexConstantBufferData.pSysMem = &VertexConstant;

					//Creating the buffer.
					DebugCode DEBUGCODE = Graphics->GetDevice()->CreateBuffer(&NewVertexConstantBufferDESC, &NewVertexConstantBufferData, mConstantBuffer.GetAddressOf());

					if (DEBUGCODE == S_OK)
					{
						mConstantBuffer = NewVertexConstantBuffer;
					}
					else
					{
						MB_EXCEPTION(DEBUGCODE);
					}
				}
			public:
				ID3D11Buffer* GetVertexConstantBuffer() const { return mConstantBuffer.Get(); }
			};

			template <class PixelConstantTemplateType>
			class PixelConstantBuffer : public ConstantBuffer<PixelConstantTemplateType>
			{
				using ConstantBuffer<PixelConstantTemplateType>::mConstantBuffer; //Using mConstantBuffer Variable From ConstantBuffer Class
			public:
				using ConstantBuffer<PixelConstantTemplateType>::ConstantBuffer; //Using ConstantBuffer Constructor
				void Bind() override { this->Graphics->GetContext()->PSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf()); }
				/// <summary>
				/// Replace the old PixelConstantBuffer with the new one that user specifies.
				/// Note: This Method needs Improvement for the third parameter, Perphaps PixelConstantBuffer class could hold the passed PixelConstantBuffer onto the Memomry in the future.
				/// </summary>
				void Replace(const PixelConstantBuffer& PixelConstantBuffer, const PixelConstantTemplateType& PixelConstant)
				{
					//Releasing the already existing data in the buffer.
					mConstantBuffer->Release();

					//Copying the new buffer and getting its description.
					Microsoft::WRL::ComPtr<ID3D11Buffer> NewPixelConstantBuffer = PixelConstantBuffer.GetPixelConstantBuffer();
					D3D11_BUFFER_DESC NewPixelConstantBufferDESC{};
					NewPixelConstantBuffer.Get()->GetDesc(&NewPixelConstantBufferDESC);
					D3D11_SUBRESOURCE_DATA NewPixelConstantBufferData{};
					NewPixelConstantBufferData.pSysMem = &PixelConstant;

					//Creating the buffer.
					DebugCode DEBUGCODE = Graphics->GetDevice()->CreateBuffer(&NewPixelConstantBufferDESC, &NewPixelConstantBufferData, mConstantBuffer.GetAddressOf());

					if (DEBUGCODE == S_OK)
					{
						mConstantBuffer = NewPixelConstantBuffer;
					}
					else
					{
						MB_EXCEPTION(DEBUGCODE);
					}
				}
			public:
				ID3D11Buffer* GetPixelConstantBuffer() const { return mConstantBuffer.Get(); }
			};
		}
	}
}
