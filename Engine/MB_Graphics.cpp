#include "MB_Graphics.h"

MafiaBar::Graphics::Graphics(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	//Changing to The Width And Height of the Windows
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;

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
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
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

	//Creating Depth And Stencil View Buffer 
	Microsoft::WRL::ComPtr<ID3D11Resource> m_BackBufferDepthStencilView = nullptr;
	m_Swap->GetBuffer(0, __uuidof(ID3D11Resource), &m_BackBufferDepthStencilView);
	m_Device->CreateDepthStencilView(m_BackBufferDepthStencilView.Get(), nullptr, &m_DepthStencilView);
}

void MafiaBar::Graphics::EndFrame() { m_Swap->Present(1u, 0u); }

void MafiaBar::Graphics::SetViewport(const D3D11_VIEWPORT& Viewport, uint32_t ViewportsNumbers) { m_Context->RSSetViewports(ViewportsNumbers, &Viewport); }

void MafiaBar::Graphics::Clear(const float ClearRenderColor[4], float ClearDepthBuffer, UINT8 ClearStencilBuffer)
{
	m_Context->ClearRenderTargetView(m_RenderTarget.Get(), ClearRenderColor);
	m_Context->ClearDepthStencilView(m_DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, ClearDepthBuffer, ClearStencilBuffer);
}

ID3D11Device* MafiaBar::Graphics::GetDevice() const { return m_Device.Get(); }

IDXGISwapChain* MafiaBar::Graphics::GetSwap() const { return m_Swap.Get(); }

ID3D11DeviceContext* MafiaBar::Graphics::GetContext() const { return m_Context.Get(); }

ID3D11RenderTargetView* MafiaBar::Graphics::GetRenderTarget() const { return m_RenderTarget.Get(); }

ID3D11DepthStencilView* MafiaBar::Graphics::GetDepthStencilView() const { return m_DepthStencilView.Get(); }
