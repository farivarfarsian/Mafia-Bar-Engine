#pragma once
#include "GraphicsPipline.h"


class Cube : public MafiaBar::Engine::Graphics::Object
{
public:
	Cube(MafiaBar::Engine::Graphics::Graphics& graphics, std::mt19937& rng, std::uniform_real_distribution<float>& adist, std::uniform_real_distribution<float>& ddist, std::uniform_real_distribution<float>& odist, std::uniform_real_distribution<float>& rdist)
		: r(rdist(rng)), droll(ddist(rng)), dpitch(ddist(rng)), dyaw(ddist(rng)), dphi(odist(rng)), dtheta(odist(rng)), dchi(odist(rng)), chi(adist(rng)), theta(adist(rng)), phi(adist(rng))
	{
		MafiaBar::Graphics::Vertex vertices[] =
		{
			{ -1.0f,-1.0f,-1.0f },
			{ 1.0f,-1.0f,-1.0f },
			{ -1.0f,1.0f,-1.0f },
			{ 1.0f,1.0f,-1.0f },
			{ -1.0f,-1.0f,1.0f },
			{ 1.0f,-1.0f,1.0f },
			{ -1.0f,1.0f,1.0f },
			{ 1.0f,1.0f,1.0f },
		};

		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::VertexBuffer>(graphics, vertices));


		const MafiaBar::SDK::Vector<uint16_t> indicies =
		{
			0,2,1, 2,3,1,
			1,3,5, 3,7,5,
			2,6,3, 3,6,7,
			4,5,7, 4,7,6,
			0,4,2, 2,4,6,
			0,1,4, 1,5,4
		};
		auto IndexBufferP = std::make_unique<MafiaBar::Engine::Graphics::IndexBuffer>(graphics, indicies);
		indexbuffer = IndexBufferP.get();
		pipeline.BindToPipline(std::move(IndexBufferP));


		auto pvs = std::make_unique<MafiaBar::Engine::Graphics::VertexShader>(graphics, "Shaders/VertexShader.cso");
		auto pvsbc = pvs->GetShaderBlob();
		pipeline.BindToPipline(std::move(pvs));

		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::TransformCbuf>(graphics, this));

		const MafiaBar::Graphics::ConstantBuffer2 cb2 =
		{
			{
				{ 1.0f,0.0f,1.0f },
				{ 1.0f,0.0f,0.0f },
				{ 0.0f,1.0f,0.0f },
				{ 0.0f,0.0f,1.0f },
				{ 1.0f,1.0f,0.0f },
				{ 0.0f,1.0f,1.0f },
			}
		};
		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::PixelConstantBuffer<MafiaBar::Graphics::ConstantBuffer2>>(graphics, cb2));

		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::PixelShader>(graphics, "Shaders/PixelShader.cso"));

		MafiaBar::SDK::Vector<D3D11_INPUT_ELEMENT_DESC> ied;
			ied.PushBack({"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0});
		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::InputLayout>(graphics, ied, pvsbc));

		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::Topology>(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));


		pipeline.BindToPipline(std::make_unique<MafiaBar::Engine::Graphics::Viewport>(graphics, 1200, 800));
	}
	void Draw(MafiaBar::Engine::Graphics::Graphics& graphics) override
	{
		pipeline.BindThePipline(graphics);
		graphics.DrawIndexed(indexbuffer->GetIndiciesCount());
	}
	void Update(float delta_time) override
	{
		roll += droll * delta_time;
		pitch += dpitch * delta_time;
		yaw += dyaw * delta_time;
		theta += dtheta * delta_time;
		phi += dphi * delta_time;
		chi += dchi * delta_time;
	}
	DirectX::XMMATRIX GetTransformation() const override
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll) *
			DirectX::XMMatrixTranslation(r, 0.0f, 0.0f) *
			DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi) *
			DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
	}
private:
	MafiaBar::Engine::Graphics::Pipline pipeline;
	const MafiaBar::Engine::Graphics::IndexBuffer* indexbuffer = nullptr;
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
};