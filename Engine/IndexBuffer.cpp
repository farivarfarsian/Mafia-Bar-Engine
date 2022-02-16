#include "IndexBuffer.h"

MafiaBar::Engine::Graphics::IndexBuffer::IndexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, const MafiaBar::SDK::Vector<unsigned short>& indices)
	: Count((unsigned int)indices.GetSize())
{
	D3D11_BUFFER_DESC IndexBufferDECRIBTOR = {};
	IndexBufferDECRIBTOR.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IndexBufferDECRIBTOR.ByteWidth = UINT(indices.GetSize() * sizeof(unsigned short));
	IndexBufferDECRIBTOR.CPUAccessFlags = 0u;
	IndexBufferDECRIBTOR.MiscFlags = 0u;
	IndexBufferDECRIBTOR.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA IndexSUBRESOURCE_DATA;
	IndexSUBRESOURCE_DATA.pSysMem = indices.GetData();
	MB_GRAPHIC_EXCEPTION(graphics.GetDevice()->CreateBuffer(&IndexBufferDECRIBTOR, &IndexSUBRESOURCE_DATA, &m_IndexBuffer));
}

void MafiaBar::Engine::Graphics::IndexBuffer::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, Offset); }

unsigned int MafiaBar::Engine::Graphics::IndexBuffer::GetIndexBufferOffset() const { return Offset; }

unsigned int MafiaBar::Engine::Graphics::IndexBuffer::GetIndiciesCount() const { return Count; }
