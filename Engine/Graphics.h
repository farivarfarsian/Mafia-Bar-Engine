#pragma once
#include "Engine.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE Graphics
			{
				friend class Bindable;
			public:
				//Initialize DirectX 11
				Graphics(HWND hwnd, int Width, int Height);
				Graphics(const Graphics&) = delete;
				Graphics& operator=(const Graphics&) = delete;
				~Graphics() = default;
			public:
				//Set Graphics Projection
				void SetProjection(DirectX::FXMMATRIX projection);
				//Draw Indexed Indicies 
				void DrawIndexed(unsigned int Count);
				// This functions clears the both Back buffer and the Depth and Stencil buffer
				void Clear(const float ClearRenderColor[4], float ClearDepthBuffer, UINT8 ClearStencilBuffer);
				void Clear(float ClearRenderColorR, float ClearRenderColorG, float ClearRenderColorB, float ClearRenderColorA, float ClearDepthBuffer, UINT8 ClearStencilBuffer);
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
				//Get Width of the Window
				int GetWidth() const;
				//Get Height of the Window
				int GetHeight() const;
				//Get Graphics Projection
				DirectX::XMMATRIX GetProjection() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
				Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context = nullptr;
				Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTarget = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
				DirectX::XMMATRIX m_ProjectionGraphics;
				int Width, Height;
			};
			class Object
			{
			public:
				virtual void Input() {};
				virtual void Update(float delta_time) {};
				virtual void Draw(MafiaBar::Engine::Graphics::Graphics& graphics) {};
				virtual DirectX::XMMATRIX GetTransformation() const { return DirectX::XMMATRIX(); };
			};
		}
	}
}

