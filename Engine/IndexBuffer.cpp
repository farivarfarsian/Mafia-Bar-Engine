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
	MB_EXCEPTION(graphics.GetDevice()->CreateBuffer(&IndexBufferDECRIBTOR, &IndexSUBRESOURCE_DATA, &m_IndexBuffer));
}

void MafiaBar::Engine::Graphics::IndexBuffer::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, Offset); }

void MafiaBar::Engine::Graphics::IndexBuffer::Replace(Graphics& Graphics, const IndexBuffer& IndexBuffer, const MafiaBar::SDK::Vector<unsigned short>& Indices)
{
	//Releasing the already existing data from the buffer.
	m_IndexBuffer->Release();

	//Copying IndexBuffer and getting its description.
	Microsoft::WRL::ComPtr<ID3D11Buffer> NewVertexBuffer = IndexBuffer.GetIndexBuffer();
	D3D11_BUFFER_DESC NewVertexBufferDECRIBTOR{};
	NewVertexBuffer->GetDesc(&NewVertexBufferDECRIBTOR);

	D3D11_SUBRESOURCE_DATA NewVertexSUBRESOURCE_DATA{};
	NewVertexSUBRESOURCE_DATA.pSysMem = Indices.GetData();

	//Creating the new IndexBuffer
	DebugCode DEBUGCODE = Graphics.GetDevice()->CreateBuffer(&NewVertexBufferDECRIBTOR, &NewVertexSUBRESOURCE_DATA, m_IndexBuffer.GetAddressOf());

	//Copying the new created buffer into the IndexBuffer class buffer
	if (DEBUGCODE == S_OK)
	{
		m_IndexBuffer = NewVertexBuffer;
	}
	else
	{
		MB_EXCEPTION(DEBUGCODE);
	}

	//Copying other data from IndexBuffer and replacing them.
	this->Count = IndexBuffer.GetIndiciesCount();
	this->Offset = IndexBuffer.GetIndexBufferOffset();
}

ID3D11Buffer* MafiaBar::Engine::Graphics::IndexBuffer::GetIndexBuffer() const { return m_IndexBuffer.Get(); }

unsigned int MafiaBar::Engine::Graphics::IndexBuffer::GetIndexBufferOffset() const { return Offset; }

unsigned int MafiaBar::Engine::Graphics::IndexBuffer::GetIndiciesCount() const { return Count; }
