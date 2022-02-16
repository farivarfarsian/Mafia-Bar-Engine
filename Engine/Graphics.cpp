#include "Graphics.h"

MafiaBar::Engine::Graphics::Graphics::Graphics(HWND hwnd, int Width, int Height)
	: Width(Width), Height(Height)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	//Changing to The Width And Height of the Windows
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;

	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //Pixel Layouts

	//Picking the default Refreshrate
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;

	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	//Disabling Antialiasing
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	// Using this Buffer for the Render Target (one Back Buffer, one Front Buffer)
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;

	//Window Stuff (Handle, Windowed)
	sd.OutputWindow = hwnd;
	sd.Windowed = true;

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//No Flags
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	UINT swapCreateFlags = 0u;
#ifndef _CRT_SECURE_NO_WARNINGS_CRT_SECURE_NO_WARNINGSNDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_Swap,
		&m_Device,
		nullptr,
		&m_Context
	);

	//Creating Render Target View
	Microsoft::WRL::ComPtr<ID3D11Resource> m_BackBuffer = nullptr;
	m_Swap->GetBuffer(0, __uuidof(ID3D11Resource), &m_BackBuffer);
	m_Device->CreateRenderTargetView(m_BackBuffer.Get(), nullptr, &m_RenderTarget);

	//Creating Depth And Stencil State Buffer 
	D3D11_DEPTH_STENCIL_DESC DepthStencilBufferDESC = {};
	DepthStencilBufferDESC.DepthEnable = TRUE;
	DepthStencilBufferDESC.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilBufferDESC.DepthFunc = D3D11_COMPARISON_LESS;
	m_Device->CreateDepthStencilState(&DepthStencilBufferDESC, &m_DepthStencilState);
	//bind depth state
	m_Context->OMSetDepthStencilState(m_DepthStencilState.Get(), 1u);

	//create depth stencil texture
	Microsoft::WRL::ComPtr<ID3D11Texture2D> DepthStencilTexure;
	D3D11_TEXTURE2D_DESC DepthStencilTextureDESC = {};
	DepthStencilTextureDESC.Width = Width;
	DepthStencilTextureDESC.Height = Height;
	DepthStencilTextureDESC.MipLevels = 1u;
	DepthStencilTextureDESC.ArraySize = 1u;
	DepthStencilTextureDESC.Format = DXGI_FORMAT_D32_FLOAT;
	DepthStencilTextureDESC.SampleDesc.Count = 1u;
	DepthStencilTextureDESC.SampleDesc.Quality = 0u;
	DepthStencilTextureDESC.Usage = D3D11_USAGE_DEFAULT;
	DepthStencilTextureDESC.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_Device->CreateTexture2D(&DepthStencilTextureDESC, nullptr, &DepthStencilTexure);


	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDESC = {};
	DepthStencilViewDESC.Format = DXGI_FORMAT_D32_FLOAT;
	DepthStencilViewDESC.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDESC.Texture2D.MipSlice = 0u;
	m_Device->CreateDepthStencilView(DepthStencilTexure.Get(), &DepthStencilViewDESC, &m_DepthStencilView);

	m_Context->OMSetRenderTargets(1u, m_RenderTarget.GetAddressOf(), m_DepthStencilView.Get());


}

void MafiaBar::Engine::Graphics::Graphics::EndFrame() { m_Swap->Present(1u, 0u); }

void MafiaBar::Engine::Graphics::Graphics::CreateSprite(const wchar_t* font_path)
{
	m_SpriteBatch = std::make_unique<DirectX::SpriteBatch>(m_Context.Get());
	m_SpriteFont = std::make_unique<DirectX::SpriteFont>(m_Device.Get(), font_path);
}

void MafiaBar::Engine::Graphics::Graphics::DrawIndexed(unsigned int Count) { m_Context->DrawIndexed(Count, 0u, 0u); }

void MafiaBar::Engine::Graphics::Graphics::Clear(const float ClearRenderColor[4], float ClearDepthBuffer, UINT8 ClearStencilBuffer)
{
	m_Context->ClearRenderTargetView(m_RenderTarget.Get(), ClearRenderColor);
	m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, ClearDepthBuffer, ClearStencilBuffer);
}

void MafiaBar::Engine::Graphics::Graphics::Clear(float ClearRenderColorR, float ClearRenderColorG, float ClearRenderColorB, float ClearRenderColorA, float ClearDepthBuffer, UINT8 ClearStencilBuffer)
{
	const float color[] = { ClearRenderColorR,ClearRenderColorG, ClearRenderColorB, ClearRenderColorA};
	m_Context->ClearRenderTargetView(m_RenderTarget.Get(), color);
	m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, ClearDepthBuffer, ClearStencilBuffer);
}

ID3D11Device* MafiaBar::Engine::Graphics::Graphics::GetDevice() const { return m_Device.Get(); }

IDXGISwapChain* MafiaBar::Engine::Graphics::Graphics::GetSwap() const { return m_Swap.Get(); }

ID3D11DeviceContext* MafiaBar::Engine::Graphics::Graphics::GetContext() const { return m_Context.Get(); }

ID3D11RenderTargetView* MafiaBar::Engine::Graphics::Graphics::GetRenderTarget() const { return m_RenderTarget.Get(); }

ID3D11DepthStencilState* MafiaBar::Engine::Graphics::Graphics::GetDepthStencilState() const { return m_DepthStencilState.Get(); }

ID3D11DepthStencilView* MafiaBar::Engine::Graphics::Graphics::GetDepthStencilView() const { return m_DepthStencilView.Get(); }

int MafiaBar::Engine::Graphics::Graphics::GetWidth() const { return Width; }

int MafiaBar::Engine::Graphics::Graphics::GetHeight() const { return Height; }

DirectX::XMMATRIX MafiaBar::Engine::Graphics::Graphics::GetProjection() const { return m_ProjectionGraphics; }

DirectX::SpriteBatch* MafiaBar::Engine::Graphics::Graphics::GetSpriteBatch() const { return m_SpriteBatch.get(); }

DirectX::SpriteFont* MafiaBar::Engine::Graphics::Graphics::GetSpriteFont() const { return m_SpriteFont.get(); }

void MafiaBar::Engine::Graphics::Graphics::SetProjection(DirectX::FXMMATRIX projection) { m_ProjectionGraphics = projection; }
