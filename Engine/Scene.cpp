#include "Scene.h"
#include "Engine.h"//Using Engine::Get().GetUI()

void MafiaBar::Engine::Scene::Initialize(MafiaBar::Engine::Graphics::Graphics* Graphics)
{
	if (Graphics == nullptr)
	{
		return;
	}
	m_Graphics = Graphics;

	m_SceneViewport = { 0.0f, 0.0f, m_Graphics->GetWidth(), m_Graphics->GetHeight(), 0.0f, 1.0f };
	m_SceneProjection = DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f);
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

void MafiaBar::Engine::Scene::SetSceneViewport(const D3D11_VIEWPORT& Viewport)
{
	m_SceneViewport.TopLeftX = Viewport.TopLeftX;
	m_SceneViewport.TopLeftY = Viewport.TopLeftY;
	m_SceneViewport.Width = Viewport.Width;
	m_SceneViewport.Height = Viewport.Height;
	m_SceneViewport.MinDepth = Viewport.MinDepth;
	m_SceneViewport.MaxDepth = Viewport.MaxDepth;
}

void MafiaBar::Engine::Scene::NewFrame()
{
	m_Graphics->GetContext()->OMSetRenderTargets(1u, m_Graphics->GetRenderTargetPP(), m_Graphics->GetDepthStencilView());

	Clear(1.0f, 0);

	Engine::Get().GetUI().NewFrame();
}

void MafiaBar::Engine::Scene::Render()
{
	for (auto&[ID, Entity] : Entities)
	{
		Entity->Input();
		Entity->Update(m_DeltaTime);
		Entity->Draw(*m_Graphics);
	}

	Engine::Get().GetUI().Render();

	if (m_Graphics->GetVsyncBoolean() == true) { m_Graphics->GetSwap()->Present(1u, 0u); }
	else if (m_Graphics->GetVsyncBoolean() == false) { m_Graphics->GetSwap()->Present(0, 0); }
}

void MafiaBar::Engine::Scene::AddEntity(const std::shared_ptr<Entity>& Entity)
{
	Entities[Entity->GetEntityID()] = Entity; //Copying the l-value.
}

void MafiaBar::Engine::Scene::AddEntity(std::shared_ptr<Entity>&& Entity)
{
	Entities[Entity->GetEntityID()] = std::move(Entity); //Moving the r-value. 
}

void MafiaBar::Engine::Scene::DeleteEntity(EntityID EntityID)
{
	Entities.erase(EntityID);
}

MafiaBar::Engine::Entity* MafiaBar::Engine::Scene::GetEntity(EntityID EntityID)
{
	return Entities.at(EntityID).get();
}

DirectX::XMMATRIX MafiaBar::Engine::Scene::GetSceneProjection() const 
{ 
	return m_SceneProjection; 
}

D3D11_VIEWPORT MafiaBar::Engine::Scene::GetSceneViewport() const
{
	return m_SceneViewport;
}

const float* MafiaBar::Engine::Scene::GetSceneClearColor() const
{
	return m_SceneClearColor;
}

float MafiaBar::Engine::Scene::GetDeltaTime() const
{
	return m_DeltaTime;
}
