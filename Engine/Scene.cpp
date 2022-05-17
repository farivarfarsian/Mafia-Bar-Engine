#include "Scene.h"

void MafiaBar::Engine::Scene::Initialize(MafiaBar::Engine::Graphics::Graphics* Graphics)
{
	m_Graphics = Graphics;
}

void MafiaBar::Engine::Scene::Clear(const float ClearRenderColor[4], float ClearDepthBuffer, UINT8 ClearStencilBuffer)
{
	m_Graphics->GetContext()->ClearRenderTargetView(m_Graphics->GetRenderTarget(), ClearRenderColor);
	m_Graphics->GetContext()->ClearDepthStencilView(m_Graphics->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, ClearDepthBuffer, ClearStencilBuffer);
}

void MafiaBar::Engine::Scene::Clear(float R, float G, float B, float A, float ClearDepthBuffer, UINT8 ClearStencilBuffer)
{
	const float Color[] = { R, G, B, A };
	m_Graphics->GetContext()->ClearRenderTargetView(m_Graphics->GetRenderTarget(), Color);
	m_Graphics->GetContext()->ClearDepthStencilView(m_Graphics->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, ClearDepthBuffer, ClearStencilBuffer);
}

void MafiaBar::Engine::Scene::SetSceneProjection(const DirectX::FXMMATRIX& Projection) 
{ 
	m_SceneProjection = Projection; 
}

void MafiaBar::Engine::Scene::Render()
{	
	if (m_Graphics->GetVsyncBoolean() == true) { m_Graphics->GetSwap()->Present(1u, 0u); }
	else if (m_Graphics->GetVsyncBoolean() == false) { m_Graphics->GetSwap()->Present(0, 0); }
}

DirectX::XMMATRIX MafiaBar::Engine::Scene::GetSceneProjection() const 
{ 
	return m_SceneProjection; 
}
