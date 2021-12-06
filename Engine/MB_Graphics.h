#pragma once
#include "../Mafia Bar Engine/pch.h"


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
			//	m_Context->Draw(3u, 0u);
		}
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

