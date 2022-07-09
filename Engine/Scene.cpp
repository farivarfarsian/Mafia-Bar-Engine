#include "Scene.h"

void MafiaBar::Engine::Scene::Initialize(MafiaBar::Engine::Graphics::Graphics* Graphics)
{
	m_Graphics = Graphics;
}

void MafiaBar::Engine::Scene::Clear(float ClearDepthBuffer, UINT8 ClearStencilBuffer)
{
	m_Graphics->GetContext()->ClearRenderTargetView(m_Graphics->GetRenderTarget(), m_SceneClearColor);
	m_Graphics->GetContext()->ClearDepthStencilView(m_Graphics->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, ClearDepthBuffer, ClearStencilBuffer);
}

void MafiaBar::Engine::Scene::SetSceneClearColor(const float ClearRenderColor[4])
{
	m_SceneClearColor[0] = ClearRenderColor[0]; //R
	m_SceneClearColor[1] = ClearRenderColor[1]; //G
	m_SceneClearColor[2] = ClearRenderColor[2]; //B
	m_SceneClearColor[3] = ClearRenderColor[3]; //A
}

void MafiaBar::Engine::Scene::SetSceneClearColor(float R, float G, float B, float A)
{
	m_SceneClearColor[0] = R;
	m_SceneClearColor[1] = G;
	m_SceneClearColor[2] = B;
	m_SceneClearColor[3] = A;
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

const float* MafiaBar::Engine::Scene::GetSceneClearColor() const
{
	return m_SceneClearColor;
}
