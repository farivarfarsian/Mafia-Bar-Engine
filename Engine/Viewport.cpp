#include "Viewport.h"

MafiaBar::Engine::Graphics::Viewport::Viewport()
	: Viewport((float)Graphics->GetWidth(), (float)Graphics->GetHeight())
{}

MafiaBar::Engine::Graphics::Viewport::Viewport(float Width, float Height)
{
	mViewport.Width = Width;
	mViewport.Height = Height;
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
	mViewport.TopLeftX = 0.0f;
	mViewport.TopLeftY = 0.0f;
}

void MafiaBar::Engine::Graphics::Viewport::Bind() { Graphics->GetContext()->RSSetViewports(1u, &mViewport); }

void MafiaBar::Engine::Graphics::Viewport::Replace(const D3D11_VIEWPORT& Viewport) { this->mViewport = Viewport; }

D3D11_VIEWPORT MafiaBar::Engine::Graphics::Viewport::GetViewport() const { return mViewport; }
