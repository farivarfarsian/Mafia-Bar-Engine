#include "VertexBuffer.h"

void MafiaBar::Engine::Graphics::VertexBuffer::Bind(MafiaBar::Engine::Graphics::Graphics& graphics) { graphics.GetContext()->IASetVertexBuffers(0u, 1u, m_VertexBuffer.GetAddressOf(), &VertexBufferStride, &Offset); }

unsigned int MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBufferStride() const { return VertexBufferStride; }

unsigned int MafiaBar::Engine::Graphics::VertexBuffer::GetVertexBufferOffset() const { return Offset; }
