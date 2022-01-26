#include "ConstantBuffer.h"

template<class ConstantTemplateType>
MafiaBar::Engine::Graphics::ConstantBuffer<ConstantTemplateType>::ConstantBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const ConstantTemplateType& ConstantType)
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
	graphics.GetDevice()->CreateBuffer(&ConstantBufferDECRIBTOR, &ConstantSUBRESOURCE_DATA, &mConstantBuffer);
}

template<class ConstantTemplateType>
MafiaBar::Engine::Graphics::ConstantBuffer<ConstantTemplateType>::ConstantBuffer(MafiaBar::Engine::Graphics::Graphics& graphics)
{
	D3D11_BUFFER_DESC ConstantBufferDECRIBTOR = {};
	ConstantBufferDECRIBTOR.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDECRIBTOR.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDECRIBTOR.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDECRIBTOR.MiscFlags = 0u;
	ConstantBufferDECRIBTOR.ByteWidth = sizeof(ConstantTemplateType);
	ConstantBufferDECRIBTOR.StructureByteStride = 0u;
	graphics.GetDevice()->CreateBuffer(&ConstantBufferDECRIBTOR, nullptr, &mConstantBuffer);
}

template<class ConstantTemplateType>
void MafiaBar::Engine::Graphics::ConstantBuffer<ConstantTemplateType>::Update(MafiaBar::Engine::Graphics::Graphics& graphics, const ConstantTemplateType& ConstantType)
{
	D3D11_MAPPED_SUBRESOURCE MappedSubSource;
	graphics.GetContext()->Map(mConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &MappedSubSource);
	memcpy(MappedSubSource.pData, &ConstantType, sizeof(ConstantType));
	graphics.GetContext()->Unmap(mConstantBuffer.Get(), 0u);
}

template<class VertexConstantTemplateType>
void MafiaBar::Engine::Graphics::VertexConstantBuffer<VertexConstantTemplateType>::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->VSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf()); }

template<class PixelConstantTemplateType>
void MafiaBar::Engine::Graphics::PixelConstantBuffer<PixelConstantTemplateType>::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->PSSetConstantBuffers(0u, 1u, mConstantBuffer.GetAddressOf()); }