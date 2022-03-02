#pragma once
#include "Definitions.h"
#include "pch.h"

#include "Exception.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API Graphics final
			{
				friend class Bindable;
			public:
				//Initialize DirectX 11
				Graphics(HWND hwnd, int O_Width, int O_Height, bool Fullscreen, bool Vsync);
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
				//Initializing Sprite Font
				void CreateSprite(const wchar_t* path_name);
				//Take a screenshot of what you're rendering(screen)
				void ScreenShot() const
				{				
	  				ID3D11Texture2D* BackBuffer = nullptr;
					MB_EXCEPTION(m_Swap->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer)));
					MB_EXCEPTION(DirectX::SaveWICTextureToFile(m_Context.Get(), BackBuffer, GUID_ContainerFormatJpeg, L"Screenshot.jpg"));
					BackBuffer->Release();
					BackBuffer = 0;
				}
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
				//Get Sprite Batch
				DirectX::SpriteBatch* GetSpriteBatch() const;
				//Get Sprite Font
				DirectX::SpriteFont* GetSpriteFont() const;
				//Get VideoCard memory size in MBs
				const unsigned long GetGraphicCardMemorySize() const;
				//Get VideoCard description
				const char* GetGraphicCardDescription() const;
				//Get Vsync Boolean
				const bool GetVsyncBoolean() const;
				//Get GraphicCard informations with a pair, first element is description and the second one is the size of its memory
				constexpr std::pair<const char*, unsigned long> GetGraphicCardInfo() const;
			private:
				Microsoft::WRL::ComPtr<ID3D11Device> m_Device = nullptr;
				Microsoft::WRL::ComPtr<IDXGISwapChain> m_Swap = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_Context = nullptr;
				Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTarget = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState = nullptr;
				Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView = nullptr;
				Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_RasterizerState = nullptr;
				Microsoft::WRL::ComPtr<ID3D11BlendState> m_BlendState = nullptr;
				std::unique_ptr<DirectX::SpriteBatch> m_SpriteBatch = nullptr;
				std::unique_ptr<DirectX::SpriteFont> m_SpriteFont = nullptr;
				DirectX::XMMATRIX m_ProjectionGraphics;
				int Width, Height;
				bool m_Vsync = false;
				char m_GraphicCardDescription[MAX_PATH];
				unsigned long m_GraphicCardMemorySize = 0;
				unsigned int Numerator = 0;
				unsigned int Denominator = 0;
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

