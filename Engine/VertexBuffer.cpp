#include "VertexBuffer.h"

MafiaBar::Engine::Graphics::VertexBuffer::VertexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, MafiaBar::Graphics::Vertex* vertices)
	: VertexBufferStride(sizeof(MafiaBar::Graphics::Vertex))
{
	D3D11_BUFFER_DESC VertexBufferDECRIBTOR;
	VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
	VertexBufferDECRIBTOR.MiscFlags = 0u;
	VertexBufferDECRIBTOR.ByteWidth = sizeof(vertices);
	VertexBufferDECRIBTOR.StructureByteStride = sizeof(MafiaBar::Graphics::Vertex);
	D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
	VertexSUBRESOURCE_DATA.pSysMem = static_cast<const void*>(&vertices);
	graphics.GetDevice()->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &m_VertexBuffer);
}

MafiaBar::Engine::Graphics::VertexBuffer::VertexBuffer(MafiaBar::Engine::Graphics::Graphics& graphics, MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& vertices)
	: VertexBufferStride(sizeof(MafiaBar::Graphics::Vertex))
{
	D3D11_BUFFER_DESC VertexBufferDECRIBTOR;
	VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
	VertexBufferDECRIBTOR.MiscFlags = 0u;
	VertexBufferDECRIBTOR.ByteWidth = unsigned int(sizeof(MafiaBar::Graphics::Vertex) * vertices.GetSize());
	VertexBufferDECRIBTOR.StructureByteStride = sizeof(MafiaBar::Graphics::Vertex);
	D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
	VertexSUBRESOURCE_DATA.pSysMem = vertices.GetData();
	graphics.GetDevice()->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &m_VertexBuffer);
}

void MafiaBar::Engine::Graphics::VertexBuffer::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &VertexBufferStride, &Offset); }

unsigned int MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBufferStride() const { return VertexBufferStride; }

unsigned int MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBufferOffset() const { return Offset; }
