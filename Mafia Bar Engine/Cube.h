#pragma once
#include "Engine.h"
#include "Pipeline.h"

//Components
#include "Transform.h"
#include "MeshComponent.h"

class Cube : public MafiaBar::Engine::Entity
{
public:
	Cube()
	{
		Assign<MafiaBar::Engine::TransformComponent>(*new MafiaBar::Engine::TransformComponent({ 0.0f, 0.0f, 5.0f}, { 1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f, 0.0f}));
		Assign<MafiaBar::Engine::MeshComponent>(*new MafiaBar::Engine::MeshComponent(
				{//Vertices
					{ -1.0f, -1.0f, -1.0f },
					{ 1.0f, -1.0f, -1.0f },
					{ -1.0f, 1.0f, -1.0f },
					{ 1.0f, 1.0f, -1.0f },
					{ -1.0f, -1.0f, 1.0f },
					{ 1.0f, -1.0f, 1.0f },
					{ -1.0f, 1.0f, 1.0f },
					{ 1.0f, 1.0f, 1.0f }
				}
			,
				{ //Indices
					0,2,1, 2,3,1,
					1,3,5, 3,7,5,
					2,6,3, 3,6,7,
					4,5,7, 4,7,6,
					0,4,2, 2,4,6,
					0,1,4, 1,5,4
				}
		));

		auto vertexshader = std::make_shared<MafiaBar::Engine::Graphics::VertexShader>(L"Shaders/VertexShader.cso");
		auto vertexshadeblob = vertexshader->GetShaderBlob();
		pipline.AddBindable(std::move(vertexshader));


		MafiaBar::Graphics::PixelConstantBufferFaceColors Face_Colors =
		{
			{
				{1.0f,0.0f,1.0f},
				{1.0f,0.0f,0.0f},
				{0.0f,1.0f,0.0f},
				{0.0f,0.0f,1.0f},
				{1.0f,1.0f,0.0f},
				{0.0f,1.0f,1.0f},
			}
		};

		pipline.AddBindable(std::make_shared<MafiaBar::Engine::Graphics::PixelConstantBuffer<MafiaBar::Graphics::PixelConstantBufferFaceColors>>(Face_Colors));

		pipline.AddBindable(std::make_shared<MafiaBar::Engine::Graphics::PixelShader>(L"Shaders/PixelShader.cso"));

		MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC> InputLayout;
		InputLayout.PushBack({ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		pipline.AddBindable(std::make_shared<MafiaBar::Engine::Graphics::InputLayout>(InputLayout, vertexshadeblob));

		pipline.AddBindable(std::make_shared<MafiaBar::Engine::Graphics::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		pipline.AddBindable(std::make_shared<MafiaBar::Engine::Graphics::Viewport>(1200.0f, 800.0f));

		pipline.AddBindable(std::make_shared<MafiaBar::Engine::Graphics::TransformCbuf>(this));
	}
	Cube(const Cube&) = default;
	Cube& operator=(const Cube&) = default;
	void Input() override
	{
		if (MafiaBar::Engine::Engine::Get().GetKeyboard().IsKeyPressed(MafiaBar::Keyboard::W) == true)
		{
			printf_s("W Key Pressed\n");
		}
	}
	void Update(float DeltaTime) override
	{

	}
	void Draw(MafiaBar::Engine::Graphics::Graphics& Graphics) override
	{
		for (auto& Component : Components)
		{
			static_cast<MafiaBar::Engine::Component*>(Component)->Run();
		}

		pipline.BindThePipline();
		Graphics.GetContext()->DrawIndexed(GetComponent<MafiaBar::Engine::MeshComponent>()->GetMesh()->GetIndicesCount(), 0u, 0u);
	}
private:
	MafiaBar::Engine::Graphics::Pipeline pipline;
};