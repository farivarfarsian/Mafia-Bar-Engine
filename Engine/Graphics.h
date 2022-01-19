#pragma once
#include "Engine.h"

namespace MafiaBar
{
	class EXP_ENGINE Graphics
	{
	public:
		Graphics(HWND hwnd, int Width, int Height);
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		~Graphics() = default;
		void TestRenderingTriangle(float angle, float x, float z)
		{
			struct Vertex
			{
				struct
				{
					float x;
					float y;
					float z;
				} position;
			};

			struct ConstantBuffer
			{
				DirectX::XMMATRIX transform;
			};

			struct ConstantBuffer2
			{
				struct
				{
					float r;
					float g;
					float b;
					float a;
				} face_colors[6];
			};

			Vertex vertices[] =
			{
				{-1.0f, -1.0f, -1.0f},
				{1.0f, -1.0f, -1.0f},
				{-1.0f, 1.0f, -1.0f},
				{1.0f, 1.0f, -1.0f},
				{-1.0f, -1.0f, 1.0f},
				{1.0f, -1.0f, 1.0f},
				{-1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f},
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

			const unsigned short indicies[] =
			{
				0,2,1, 2,3,1,
				1,3,5, 3,7,5,
				2,6,3, 3,6,7,
				4,5,7, 4,7,6,
				0,4,2, 2,4,6,
				0,1,4, 1,5,4
			};
			Microsoft::WRL::ComPtr<ID3D11Buffer> IndexBuffer;
			D3D11_BUFFER_DESC IndexBufferDECRIBTOR = {};
			IndexBufferDECRIBTOR.BindFlags = D3D11_BIND_INDEX_BUFFER;
			IndexBufferDECRIBTOR.ByteWidth = sizeof(indicies);
			IndexBufferDECRIBTOR.CPUAccessFlags = 0u;
			IndexBufferDECRIBTOR.MiscFlags = 0u;
			IndexBufferDECRIBTOR.StructureByteStride = sizeof(unsigned short);
			D3D11_SUBRESOURCE_DATA IndexSUBRESOURCE_DATA;
			IndexSUBRESOURCE_DATA.pSysMem = indicies;
			m_Device->CreateBuffer(&IndexBufferDECRIBTOR, &IndexSUBRESOURCE_DATA, &IndexBuffer);
			m_Context->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);


			Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
			Microsoft::WRL::ComPtr<ID3DBlob> VertexShaderBlob;
			D3DReadFileToBlob(L"Shaders/VertexShader.cso", &VertexShaderBlob);
			m_Device->CreateVertexShader(VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), nullptr, &VertexShader);
			m_Context->VSSetShader(VertexShader.Get(), nullptr, 0u);

			const ConstantBuffer constantbuffer =
			{
				{
					DirectX::XMMatrixTranspose(
						DirectX::XMMatrixRotationZ(angle) *
						DirectX::XMMatrixRotationX(angle) *
						DirectX::XMMatrixTranslation(x,0.0f,z + 4.0f) *
						DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.0f)
					)
				}
			};
			Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBuffer;
			D3D11_BUFFER_DESC ConstantBufferDECRIBTOR = {};
			ConstantBufferDECRIBTOR.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			ConstantBufferDECRIBTOR.Usage = D3D11_USAGE_DYNAMIC;
			ConstantBufferDECRIBTOR.ByteWidth = sizeof(constantbuffer);
			ConstantBufferDECRIBTOR.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			ConstantBufferDECRIBTOR.MiscFlags = 0u;
			ConstantBufferDECRIBTOR.StructureByteStride = 0u;
			D3D11_SUBRESOURCE_DATA ConstantSUBRESOURCE_DATA{};
			ConstantSUBRESOURCE_DATA.pSysMem = &constantbuffer;
			m_Device->CreateBuffer(&ConstantBufferDECRIBTOR, &ConstantSUBRESOURCE_DATA, &ConstantBuffer);
			m_Context->VSSetConstantBuffers(0u, 1u, ConstantBuffer.GetAddressOf());

			const ConstantBuffer2 constantbuffer2 =
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
			Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBuffer2;
			D3D11_BUFFER_DESC ConstantBufferDECRIBTOR2 = {};
			ConstantBufferDECRIBTOR2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			ConstantBufferDECRIBTOR2.Usage = D3D11_USAGE_DYNAMIC;
			ConstantBufferDECRIBTOR2.ByteWidth = sizeof(constantbuffer2);
			ConstantBufferDECRIBTOR2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			ConstantBufferDECRIBTOR2.MiscFlags = 0u;
			ConstantBufferDECRIBTOR2.StructureByteStride = 0u;
			D3D11_SUBRESOURCE_DATA ConstantSUBRESOURCE_DATA2{};
			ConstantSUBRESOURCE_DATA2.pSysMem = &constantbuffer2;
			m_Device->CreateBuffer(&ConstantBufferDECRIBTOR2, &ConstantSUBRESOURCE_DATA2, &ConstantBuffer2);
			m_Context->PSSetConstantBuffers(0u, 1u, ConstantBuffer2.GetAddressOf());

			Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
			Microsoft::WRL::ComPtr<ID3DBlob> PixelShaderBlob;


			D3DReadFileToBlob(L"Shaders/PixelShader.cso", &PixelShaderBlob);
			m_Device->CreatePixelShader(PixelShaderBlob->GetBufferPointer(), PixelShaderBlob->GetBufferSize(), nullptr, &PixelShader);
			m_Context->PSSetShader(PixelShader.Get(), nullptr, 0u);


			Microsoft::WRL::ComPtr<ID3D11InputLayout> VertexInputLayout;
			const D3D11_INPUT_ELEMENT_DESC VertexInputLayoutDESCRIPTOR[] =
			{
				{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
			};
			m_Device->CreateInputLayout(VertexInputLayoutDESCRIPTOR, (UINT)std::size(VertexInputLayoutDESCRIPTOR), VertexShaderBlob->GetBufferPointer(), VertexShaderBlob->GetBufferSize(), &VertexInputLayout);
			m_Context->IASetInputLayout(VertexInputLayout.Get());

			m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			D3D11_VIEWPORT Viewport = {};
			Viewport.Width = 1200; //1200
			Viewport.Height = 800; //800
			Viewport.MinDepth = 0;
			Viewport.MaxDepth = 1;
			Viewport.TopLeftX = 0;
			Viewport.TopLeftY = 0;
			SetViewport(Viewport, 1u);

			m_Context->DrawIndexed((UINT)std::size(indicies), 0u, 0);
		}

	public:
		// Sets D3D11 viewport (the viewports Numbers is optional by default is 1)
		void SetViewport(const D3D11_VIEWPORT& Viewport, uint32_t ViewportsNumbers = 1u);
		// This functions clears the both Back buffer and the Depth and Stencil buffer
		void Clear(const float ClearRenderColor[4], float ClearDepthBuffer, UINT8 ClearStencilBuffer);
		// Render the scene
		void EndFrame();
	public:
		//Get D3D11 Device Object
		ID3D11Device* GetDevice() const;
		//Get DXGI SwapChain Object
		IDXGISwapChain* GetSwap() const;
		//Get D3D11 Context Object
		ID3D11DeviceContext* GetContext() const;
		//Get D3D11 RenderTarget Object
		ID3D11RenderTargetView* GetRenderTarget() const;
		//Get D3D11 DepthStencilState Object
		ID3D11DepthStencilState* GetDepthStencilState() const;
		//Get D3D11 DepthStencilView Object
		ID3D11DepthStencilView* GetDepthStencilView() const;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTarget = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
	};
}

