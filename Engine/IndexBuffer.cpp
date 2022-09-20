#include "IndexBuffer.h"

MafiaBar::Engine::Graphics::IndexBuffer::IndexBuffer(const MafiaBar::SDK::Vector<unsigned short>& indices)
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
	MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&IndexBufferDECRIBTOR, &IndexSUBRESOURCE_DATA, &m_IndexBuffer));
	SetDebugCOMObjectName(m_IndexBuffer.Get(), "Index Buffer From MafiaBar::Engine::Graphics::IndexBuffer class");
}

void MafiaBar::Engine::Graphics::IndexBuffer::Bind() { Graphics->GetContext()->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, Offset); }

void MafiaBar::Engine::Graphics::IndexBuffer::Replace(const IndexBuffer& IndexBuffer)
{
	//Releasing the already existing data from the buffer.
	m_IndexBuffer->Release();

	//Copying IndexBuffer and getting its description.
	Microsoft::WRL::ComPtr<ID3D11Buffer> NewVertexBuffer = IndexBuffer.GetIndexBuffer();
	D3D11_BUFFER_DESC NewVertexBufferDECRIBTOR{};
	NewVertexBuffer->GetDesc(&NewVertexBufferDECRIBTOR);

	D3D11_SUBRESOURCE_DATA NewVertexSUBRESOURCE_DATA{};
	NewVertexSUBRESOURCE_DATA.pSysMem = IndexBuffer.GetIndicies().data();

	//Creating the new IndexBuffer
	DebugCode DEBUGCODE = Graphics->GetDevice()->CreateBuffer(&NewVertexBufferDECRIBTOR, &NewVertexSUBRESOURCE_DATA, m_IndexBuffer.GetAddressOf());

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

std::vector<unsigned short> MafiaBar::Engine::Graphics::IndexBuffer::GetIndicies() const
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer;
	D3D11_BUFFER_DESC BufferDesc{};
	m_IndexBuffer.Get()->GetDesc(&BufferDesc);
	BufferDesc.Usage = D3D11_USAGE_STAGING;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	BufferDesc.BindFlags = 0u;

	MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&BufferDesc, nullptr, Buffer.GetAddressOf()));
	Graphics->GetContext()->CopyResource(Buffer.Get(), m_IndexBuffer.Get());

	D3D11_MAPPED_SUBRESOURCE MappedSubSource;
	MB_EXCEPTION(Graphics->GetContext()->Map(Buffer.Get(), 0u, D3D11_MAP_READ, 0u, &MappedSubSource));

	std::vector<unsigned short> Indicies;
	Indicies.insert(Indicies.begin(), (unsigned short*)(MappedSubSource.pData), (unsigned short*)(MappedSubSource.pData) + sizeof(MappedSubSource.pData));

	Graphics->GetContext()->Unmap(Buffer.Get(), 0u);

	return Indicies;
}
