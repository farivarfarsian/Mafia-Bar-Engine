#pragma once
#include "Engine.h"
#include "Bindable.h"

//Note: You can't export Template Method/Constructors From a DLL. So Everything should be in the header file.

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			template <class ConstantTemplateType>
			class EXP_ENGINE ConstantBuffer : public Bindable
			{
			public:
				ConstantBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const ConstantTemplateType& ConstantType)
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
					MB_GRAPHIC_EXCEPTION(graphics.GetDevice()->CreateBuffer(&ConstantBufferDECRIBTOR, &ConstantSUBRESOURCE_DATA, &mConstantBuffer));
				}
				ConstantBuffer(MafiaBar::Engine::Graphics::Graphics& graphics)
				{
					D3D11_BUFFER_DESC ConstantBufferDECRIBTOR = {};
					ConstantBufferDECRIBTOR.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
					ConstantBufferDECRIBTOR.Usage = D3D11_USAGE_DYNAMIC;
					ConstantBufferDECRIBTOR.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
					ConstantBufferDECRIBTOR.MiscFlags = 0u;
					ConstantBufferDECRIBTOR.ByteWidth = sizeof(ConstantTemplateType);
					ConstantBufferDECRIBTOR.StructureByteStride = 0u;
					MB_GRAPHIC_EXCEPTION(graphics.GetDevice()->CreateBuffer(&ConstantBufferDECRIBTOR, nullptr, &mConstantBuffer));
				}
				void Update(MafiaBar::Engine::Graphics::Graphics& graphics, const ConstantTemplateType& ConstantType)
				{
					D3D11_MAPPED_SUBRESOURCE MappedSubSource;
					MB_GRAPHIC_EXCEPTION(graphics.GetContext()->Map(mConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &MappedSubSource));
					memcpy(MappedSubSource.pData, &ConstantType, sizeof(ConstantType));
					graphics.GetContext()->Unmap(mConstantBuffer.Get(), 0u);
				}
			protected:
				Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer;
			};

			template <class VertexConstantTemplateType>
			class EXP_ENGINE VertexConstantBuffer : public ConstantBuffer<VertexConstantTemplateType>
			{
				using ConstantBuffer<VertexConstantTemplateType>::mConstantBuffer; //Using mConstantBuffer Variable From ConstantBuffer Class
			public:
				using ConstantBuffer<VertexConstantTemplateType>::ConstantBuffer; //Using ConstantBuffer Constructor
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override { graphics.GetContext()->VSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf()); }
			};

			template <class PixelConstantTemplateType>
			class EXP_ENGINE PixelConstantBuffer : public ConstantBuffer<PixelConstantTemplateType>
			{
				using ConstantBuffer<PixelConstantTemplateType>::mConstantBuffer; //Using mConstantBuffer Variable From ConstantBuffer Class
			public:
				using ConstantBuffer<PixelConstantTemplateType>::ConstantBuffer; //Using ConstantBuffer Constructor
				void Bind(MafiaBar::Engine::Graphics::Graphics& graphics) override { graphics.GetContext()->PSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf()); }
			};
		}
	}
}
