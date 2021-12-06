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



	HRESULT hr; //Should Create This Variable For Using GFX_THROW_FAILED Macro.

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

	Microsoft::WRL::ComPtr<ID3D11Resource> m_BackBuffer = nullptr;
	m_Swap->GetBuffer(0, __uuidof(ID3D11Resource), &m_BackBuffer);
	m_Device->CreateRenderTargetView(m_BackBuffer.Get(), nullptr, &m_RenderTarget);
}

void MafiaBar::Graphics::EndFrame() { m_Swap->Present(1u, 0u); }

void MafiaBar::Graphics::ClearRenderBufferColor(float r, float g, float b, float a)
{
	const float colour[] = { r, g, b, a };
	m_Context->ClearRenderTargetView(m_RenderTarget.Get(), colour);
}

ID3D11Device* MafiaBar::Graphics::GetDevice() const { return m_Device.Get(); }

IDXGISwapChain* MafiaBar::Graphics::GetSwap() const { return m_Swap.Get(); }

ID3D11DeviceContext* MafiaBar::Graphics::GetContext() const { return m_Context.Get(); }

ID3D11RenderTargetView* MafiaBar::Graphics::GetRenderTarget() const { return m_RenderTarget.Get(); }