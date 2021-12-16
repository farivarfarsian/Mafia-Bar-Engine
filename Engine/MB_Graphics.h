#pragma once
#include "Engine.h"

namespace MafiaBar
{
	class EXP_ENGINE Graphics
	{
	public:
		Graphics(HWND hwnd);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		~Graphics() = default;
		void EndFrame();
		void ClearRenderBufferColor(float r, float g, float b, float a);
		void TestRenderingTriangle()
		{
			struct Vertex
			{
				float x;
				float y;
			};
			//creates a 2D triangle at the center of the screen
			const Vertex vertices[] =
			{
				{0.0f, 0.5f},
				{0.5f, -0.5f},
				{-0.5f, -0.5f},
			};
			D3D11_BUFFER_DESC VertexBufferDECRIBTOR;
			VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
			VertexBufferDECRIBTOR.ByteWidth = sizeof(vertices);
			VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
			VertexBufferDECRIBTOR.MiscFlags = 0u;
			VertexBufferDECRIBTOR.StructureByteStride = sizeof(Vertex);
			D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
			VertexSUBRESOURCE_DATA.pSysMem = vertices;
			Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
			m_Device->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &VertexBuffer);
			//Bind the Vertex buffer to the pipeline
			const UINT VertexBufferStride = sizeof(Vertex);
			const UINT offset = 0u;
			m_Context->IASetVertexBuffers(0u, 1u, VertexBuffer.GetAddressOf(), &VertexBufferStride, &offset);

			Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
			Microsoft::WRL::ComPtr<ID3DBlob> VertexShaderBlob;
			D3DReadFileToBlob(L"Shaders/VertexShader.cso", &VertexShaderBlob);
			m_Device->CreateVertexShader(VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), nullptr, &VertexShader);
			m_Context->VSSetShader(VertexShader.Get(), nullptr, 0u);

			Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
			Microsoft::WRL::ComPtr<ID3DBlob> PixelShaderBlob;
			D3DReadFileToBlob(L"Shaders/PixelShader.cso", &PixelShaderBlob);
			m_Device->CreatePixelShader(PixelShaderBlob->GetBufferPointer(), PixelShaderBlob->GetBufferSize(), nullptr, &PixelShader);
			m_Context->PSSetShader(PixelShader.Get(), nullptr, 0u);


			Microsoft::WRL::ComPtr<ID3D11InputLayout> VertexInputLayout;
			const D3D11_INPUT_ELEMENT_DESC VertexInputLayoutDESCRIPTOR[] = 
			{ 
				{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
			};
			m_Device->CreateInputLayout(VertexInputLayoutDESCRIPTOR, (UINT)std::size(VertexInputLayoutDESCRIPTOR), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &VertexInputLayout);
			m_Context->IASetInputLayout(VertexInputLayout.Get());

			m_Context->OMSetRenderTargets(1u, m_RenderTarget.GetAddressOf(), nullptr);

			m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			D3D11_VIEWPORT Viewport;
			Viewport.Width = 1200;
			Viewport.Height = 800;
			Viewport.MinDepth = 0;
			Viewport.MaxDepth = 1;
			Viewport.TopLeftX = 0;
			Viewport.TopLeftY = 0;
			m_Context->RSSetViewports(1u, &Viewport);

			m_Context->Draw((UINT)std::size(vertices), 0u);	
		}
		void DrawRainbowedTrinagle()
		{
			struct Vertex
			{
				Vertex() {}
				Vertex(float x, float y, float z,
					float cr, float cg, float cb, float ca)
					: pos(x, y, z), color(cr, cg, cb, ca) {}

				DirectX::XMFLOAT3 pos;
				DirectX::XMFLOAT4 color;
			};
			Vertex v[] =
			{
				Vertex(0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f),
				Vertex(0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f),
				Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
			};

			
			D3D11_BUFFER_DESC VertexBufferDECRIBTOR;
			VertexBufferDECRIBTOR.Usage = D3D11_USAGE_DEFAULT;
			VertexBufferDECRIBTOR.ByteWidth = sizeof(v);
			VertexBufferDECRIBTOR.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			VertexBufferDECRIBTOR.CPUAccessFlags = 0u;
			VertexBufferDECRIBTOR.MiscFlags = 0u;

			D3D11_SUBRESOURCE_DATA VertexSUBRESOURCE_DATA;
			VertexSUBRESOURCE_DATA.pSysMem = v;

			Microsoft::WRL::ComPtr<ID3D11Buffer> VertexBuffer;
			m_Device->CreateBuffer(&VertexBufferDECRIBTOR, &VertexSUBRESOURCE_DATA, &VertexBuffer);
			//Bind the Vertex buffer to the pipeline
			UINT VertexBufferStride = sizeof(Vertex);
			UINT offset = 0u;
			m_Context->IASetVertexBuffers(0u, 1u, VertexBuffer.GetAddressOf(), &VertexBufferStride, &offset);


			Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
			Microsoft::WRL::ComPtr<ID3DBlob> VertexShaderBlob;
			D3DReadFileToBlob(L"Shaders/VertexShaderRainbowed.cso", &VertexShaderBlob);
			m_Device->CreateVertexShader(VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), nullptr, &VertexShader);
			m_Context->VSSetShader(VertexShader.Get(), nullptr, 0u);

			Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
			Microsoft::WRL::ComPtr<ID3DBlob> PixelShaderBlob;
			D3DReadFileToBlob(L"Shaders/PixelShaderRainbowed.cso", &PixelShaderBlob);
			m_Device->CreatePixelShader(PixelShaderBlob->GetBufferPointer(), PixelShaderBlob->GetBufferSize(), nullptr, &PixelShader);
			m_Context->PSSetShader(PixelShader.Get(), nullptr, 0u);


			Microsoft::WRL::ComPtr<ID3D11InputLayout> VertexInputLayout;
			const D3D11_INPUT_ELEMENT_DESC VertexInputLayoutDESCRIPTOR[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			m_Device->CreateInputLayout(VertexInputLayoutDESCRIPTOR, (UINT)std::size(VertexInputLayoutDESCRIPTOR), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &VertexInputLayout);
			m_Context->IASetInputLayout(VertexInputLayout.Get());

			m_Context->OMSetRenderTargets(1u, m_RenderTarget.GetAddressOf(), nullptr);

			m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			D3D11_VIEWPORT Viewport;
			Viewport.Width = 1200;
			Viewport.Height = 800;
			Viewport.MinDepth = 0;
			Viewport.MaxDepth = 1;
			Viewport.TopLeftX = 0;
			Viewport.TopLeftY = 0;
			m_Context->RSSetViewports(1u, &Viewport);

			m_Context->Draw((UINT)std::size(v), 0u);
		}
	public:
		void SetViewport();
	public:
		ID3D11Device* GetDevice() const;
		IDXGISwapChain* GetSwap() const;
		ID3D11DeviceContext* GetContext() const;
		ID3D11RenderTargetView* GetRenderTarget() const;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTarget = nullptr;
	};
}

