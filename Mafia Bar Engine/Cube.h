#pragma once
#include "Engine.h"
#include "Pipeline.h"

class Cube : public MafiaBar::Engine::Entity
{
public:
	Cube(MafiaBar::Engine::Graphics::Graphics& graphics, std::mt19937& rng,
		std::uniform_real_distribution<float>& adist,
		std::uniform_real_distribution<float>& ddist,
		std::uniform_real_distribution<float>& odist,
		std::uniform_real_distribution<float>& rdist)
		:
		r(rdist(rng)),
		droll(ddist(rng)),
		dpitch(ddist(rng)),
		dyaw(ddist(rng)),
		dphi(odist(rng)),
		dtheta(odist(rng)),
		dchi(odist(rng)),
		chi(adist(rng)),
		theta(adist(rng)),
		phi(adist(rng))
	{

		MafiaBar::SDK::Vector<MafiaBar::Graphics::Vertex> vertices;
		vertices.PushBack({ -1.0f, -1.0f, -1.0f });
		vertices.PushBack({ 1.0f, -1.0f, -1.0f });
		vertices.PushBack({ -1.0f, 1.0f, -1.0f });
		vertices.PushBack({ 1.0f, 1.0f, -1.0f });
		vertices.PushBack({ -1.0f, -1.0f, 1.0f });
		vertices.PushBack({ 1.0f, -1.0f, 1.0f });
		vertices.PushBack({ -1.0f, 1.0f, 1.0f });
		vertices.PushBack({ 1.0f, 1.0f, 1.0f });

		pipline.AddBindable(new MafiaBar::Engine::Graphics::VertexBuffer(graphics, vertices));

		const MafiaBar::SDK::Vector<unsigned short> indices =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		};
		IndicesCount = (UINT)indices.GetSize();

		pipline.AddBindable(new MafiaBar::Engine::Graphics::IndexBuffer(graphics, indices));

		auto vertexshader = new MafiaBar::Engine::Graphics::VertexShader(graphics, L"Shaders/VertexShader.cso");
		auto vertexshadeblob = vertexshader->GetShaderBlob();
		pipline.AddBindable(std::move(vertexshader));


		const MafiaBar::Graphics::ConstantBuffer2 constantbuffer2 =
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

		pipline.AddBindable(new MafiaBar::Engine::Graphics::PixelConstantBuffer<MafiaBar::Graphics::ConstantBuffer2>(graphics, constantbuffer2));

		pipline.AddBindable(new MafiaBar::Engine::Graphics::PixelShader(graphics, L"Shaders/PixelShader.cso"));

		MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC> InputLayout;
		InputLayout.PushBack({ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		pipline.AddBindable(new MafiaBar::Engine::Graphics::InputLayout(graphics, InputLayout, vertexshadeblob));

		pipline.AddBindable(new MafiaBar::Engine::Graphics::Topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));

		pipline.AddBindable(new MafiaBar::Engine::Graphics::Viewport(graphics));

		pipline.AddBindable(new MafiaBar::Engine::Graphics::TransformCbuf(graphics, *this));
	}
	Cube(const Cube&) = default;
	Cube& operator=(const Cube&) = default;
	void Update(float delta_time) noexcept override
	{
		roll += droll * delta_time;
		pitch += dpitch * delta_time;
		yaw += dyaw * delta_time;
		theta += dtheta * delta_time;
		phi += dphi * delta_time;
		chi += dchi * delta_time;
	}
	DirectX::XMMATRIX GetTransformation() const noexcept override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
			DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
	}
	void Draw(MafiaBar::Engine::Graphics::Graphics& graphics) override
	{
		pipline.BindThePipline(graphics);
		graphics.DrawIndexed(IndicesCount);
	}
private:
	// positional
	float r;
	float roll = 0.0f;
	float pitch = 0.0f;
	float yaw = 0.0f;
	float theta;
	float phi;
	float chi;
	// speed (delta/s)
	float droll;
	float dpitch;
	float dyaw;
	float dtheta;
	float dphi;
	float dchi;
	MafiaBar::Engine::Graphics::Pipeline pipline;
	unsigned int IndicesCount;
};