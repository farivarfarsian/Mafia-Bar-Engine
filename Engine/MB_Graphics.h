#pragma once
#include "../Mafia Bar Engine/pch.h"


namespace MafiaBar
{
	class EXP_ENGINE Graphics
	{
	public:
		Graphics(HWND hwnd);
		//Avoiding Copying 
		Graphics(const Graphics&) = delete;
		Graphics& operator=(const Graphics&) = delete;
		~Graphics();
		void EndFrame();
		void ClearRenderBufferColor(float r, float g, float b, float a);
	public:
		ID3D11Device* GetDevice() const;
		IDXGISwapChain* GetSwap() const;
		ID3D11DeviceContext* GetContext() const;
		ID3D11RenderTargetView* GetRenderTarget() const;
	private:
		ID3D11Device* m_Device = nullptr;
		IDXGISwapChain* m_Swap = nullptr;
		ID3D11DeviceContext* m_Context = nullptr;
		ID3D11RenderTargetView* m_RenderTarget = nullptr;
	};
}

