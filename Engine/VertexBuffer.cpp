#include "VertexBuffer.h"

MafiaBar::Engine::Graphics::VertexBuffer::VertexBuffer(const MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>& Vertices)
	: VertexBufferStride(sizeof(MafiaBar::Graphics::Vertex))
{
	D3D11_BUFFER_DESC VertexBufferDECRIBTOR = {};
	VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
	VertexBufferDECRIBTOR.MiscFlags = 0u;
	VertexBufferDECRIBTOR.ByteWidth = UINT(sizeof(MafiaBar::Graphics::Vertex) * Vertices.GetSize());
	VertexBufferDECRIBTOR.StructureByteStride = sizeof(MafiaBar::Graphics::Vertex);
	D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
	VertexSUBRESOURCE_DATA.pSysMem = Vertices.GetData();
	MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &m_VertexBuffer));
	SetDebugCOMObjectName(m_VertexBuffer.Get(), "Vertex Buffer From MafiaBar::Engine::Graphics::VertexBuffer class");
}

MafiaBar::Engine::Graphics::VertexBuffer::VertexBuffer(MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex>&& Vertices)
	: VertexBufferStride(sizeof(MafiaBar::Graphics::Vertex))
{
	D3D11_BUFFER_DESC VertexBufferDECRIBTOR = {};
	VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
	VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
	VertexBufferDECRIBTOR.MiscFlags = 0u;
	VertexBufferDECRIBTOR.ByteWidth = UINT(sizeof(MafiaBar::Graphics::Vertex) * Vertices.GetSize());
	VertexBufferDECRIBTOR.StructureByteStride = sizeof(MafiaBar::Graphics::Vertex);
	D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
	VertexSUBRESOURCE_DATA.pSysMem = Vertices.GetData();
	MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &m_VertexBuffer));
	SetDebugCOMObjectName(m_VertexBuffer.Get(), "Vertex Buffer From MafiaBar::Engine::Graphics::VertexBuffer class");
}

void MafiaBar::Engine::Graphics::VertexBuffer::Bind() { Graphics->GetContext()->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &VertexBufferStride, &Offset); }

ID3D11Buffer* MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBuffer() const { return m_VertexBuffer.Get(); }

unsigned int MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBufferStride() const { return VertexBufferStride; }

unsigned int MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBufferOffset() const { return Offset; }

std::vector<MafiaBar::Graphics::Vertex> MafiaBar::Engine::Graphics::VertexBuffer::GetVertices() const
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> Buffer;
	D3D11_BUFFER_DESC BufferDesc{};
	m_VertexBuffer.Get()->GetDesc(&BufferDesc);
	BufferDesc.Usage = D3D11_USAGE_STAGING;
	BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	BufferDesc.BindFlags = 0u;

	MB_EXCEPTION(Graphics->GetDevice()->CreateBuffer(&BufferDesc, nullptr, Buffer.GetAddressOf()));
	Graphics->GetContext()->CopyResource(Buffer.Get(), m_VertexBuffer.Get());

	D3D11_MAPPED_SUBRESOURCE MappedSubSource;
	MB_EXCEPTION(Graphics->GetContext()->Map(Buffer.Get(), 0u, D3D11_MAP_READ, 0u, &MappedSubSource));

	std::vector<MafiaBar::Graphics::Vertex> Vertices;
	Vertices.insert(Vertices.begin(), (MafiaBar::Graphics::Vertex*)(MappedSubSource.pData), (MafiaBar::Graphics::Vertex*)(MappedSubSource.pData) + sizeof(MappedSubSource.pData));

	Graphics->GetContext()->Unmap(Buffer.Get(), 0u);

	return std::move(Vertices);
}

void MafiaBar::Engine::Graphics::VertexBuffer::Replace(const VertexBuffer& VertexBuffer)
{
	//Releasing the already existing data from the buffer.
	m_VertexBuffer->Release();

	//Copying VertexBuffer and getting its description.
	Microsoft::WRL::ComPtr<ID3D11Buffer> NewVertexBuffer = VertexBuffer.GetVertexBuffer();
	D3D11_BUFFER_DESC NewVertexBufferDECRIBTOR{};
	NewVertexBuffer->GetDesc(&NewVertexBufferDECRIBTOR);

	D3D11_SUBRESOURCE_DATA NewVertexSUBRESOURCE_DATA{};
	NewVertexSUBRESOURCE_DATA.pSysMem = VertexBuffer.GetVertices().data();

	//Creating the new VertexBuffer
	DebugCode DEBUGCODE = Graphics->GetDevice()->CreateBuffer(&NewVertexBufferDECRIBTOR, &NewVertexSUBRESOURCE_DATA, m_VertexBuffer.GetAddressOf());

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