#include "Graphics.h"

void MafiaBar::Engine::Graphics::Graphics::Initialize(HWND hwnd, bool Fullscreen, bool Vsync, int O_Width, int O_Height)
{
	m_Vsync = Vsync;

	if (O_Width == 0 && O_Height == 0)
	{
		RECT rect;
		if (GetClientRect(hwnd, &rect) == TRUE)
		{
			this->Width = rect.right - rect.left;
			this->Height = rect.bottom - rect.top;
		}
	}
	else if (O_Width > 0 && O_Height > 0)
	{
		this->Width = O_Width;
		this->Height = O_Height;
	}

	DXGI_SWAP_CHAIN_DESC sd = {};
	//Changing to The Width And Height of the Windows
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;

	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM; //Pixel Layouts

	if (m_Vsync == true)
	{
		sd.BufferDesc.RefreshRate.Numerator = this->Numerator;
		sd.BufferDesc.RefreshRate.Denominator = this->Denominator;
	}
	else if (m_Vsync == false)
	{
		sd.BufferDesc.RefreshRate.Numerator = 0;
		sd.BufferDesc.RefreshRate.Denominator = 0;
	}

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
	if (Fullscreen == true) { sd.Windowed = false; }
	else if (Fullscreen == false) { sd.Windowed = true; }

	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;

	unsigned int SwapDeviceCreationFlags = 0u;

#if	_CONTAINER_DEBUG_LEVEL > 0
	SwapDeviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#else
	SwapDeviceCreationFlags = 0u;
#endif //_CONTAINER_DEBUG_LEVEL > 0


	MB_EXCEPTION(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		SwapDeviceCreationFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_Swap,
		&m_Device,
		nullptr,
		&m_Context
	));

	CreateRenderTarget();

	//Creating Depth And Stencil State Buffer 
	D3D11_DEPTH_STENCIL_DESC DepthStencilBufferDESC = {};
	DepthStencilBufferDESC.DepthEnable = TRUE;
	DepthStencilBufferDESC.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilBufferDESC.DepthFunc = D3D11_COMPARISON_LESS;
	MB_EXCEPTION(m_Device->CreateDepthStencilState(&DepthStencilBufferDESC, &m_DepthStencilState));
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

	MB_EXCEPTION(m_Device->CreateTexture2D(&DepthStencilTextureDESC, nullptr, &DepthStencilTexure));


	D3D11_DEPTH_STENCIL_VIEW_DESC DepthStencilViewDESC = {};
	DepthStencilViewDESC.Format = DXGI_FORMAT_D32_FLOAT;
	DepthStencilViewDESC.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDESC.Texture2D.MipSlice = 0u;
	MB_EXCEPTION(m_Device->CreateDepthStencilView(DepthStencilTexure.Get(), &DepthStencilViewDESC, &m_DepthStencilView));

	m_Context->OMSetRenderTargets(1u, m_RenderTarget.GetAddressOf(), m_DepthStencilView.Get());


	D3D11_RASTERIZER_DESC RasterizerDesc{};
	RasterizerDesc.FillMode = D3D11_FILL_SOLID;
	RasterizerDesc.CullMode = D3D11_CULL_BACK;
	MB_EXCEPTION(m_Device->CreateRasterizerState(&RasterizerDesc, m_RasterizerState.GetAddressOf()));

	m_Context->RSSetState(m_RasterizerState.Get());
}

void MafiaBar::Engine::Graphics::Graphics::Graphics::ReceiveHardwareInformation()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adaptor = nullptr;
	IDXGIOutput* Output = nullptr;
	DXGI_MODE_DESC* DisplayModeListDesc = nullptr;
	unsigned int NumMode = 0;
	DXGI_ADAPTER_DESC AdaptorDesc{};

	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	Factory->EnumAdapters(0, &Adaptor);

	Adaptor->EnumOutputs(0, &Output);

	Output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &NumMode, 0);

	DisplayModeListDesc = new DXGI_MODE_DESC[NumMode];

	Output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &NumMode, DisplayModeListDesc);

	for (int i = 0; i < NumMode; i++)
	{
		if (DisplayModeListDesc[i].Width == (unsigned int)Width)
		{
			if (DisplayModeListDesc[i].Height == (unsigned int)Height)
			{
				Numerator = DisplayModeListDesc[i].RefreshRate.Numerator;
				Denominator = DisplayModeListDesc[i].RefreshRate.Denominator;
			}
		}
	}

	Adaptor->GetDesc(&AdaptorDesc);

	m_GraphicCardMemorySize = (((AdaptorDesc.DedicatedVideoMemory / 1024) / 1024));

	wcstombs(m_GraphicCardDescription, AdaptorDesc.Description, MAX_PATH);

	Factory->Release(); Factory = 0;
	Adaptor->Release(); Adaptor = 0;
	Output->Release(); Output = 0;
	delete[] DisplayModeListDesc;
}

void MafiaBar::Engine::Graphics::Graphics::CreateSpriteBatch()
{
	m_SpriteBatch = std::make_unique<DirectX::SpriteBatch>(m_Context.Get());
}

void MafiaBar::Engine::Graphics::Graphics::CreateCommonStates()
{
	m_CommonStates = std::make_unique<DirectX::CommonStates>(m_Device.Get());
}

void MafiaBar::Engine::Graphics::Graphics::CreateRenderTarget()
{
	Microsoft::WRL::ComPtr<ID3D11Resource> m_BackBuffer = nullptr;
	m_Swap->GetBuffer(0, __uuidof(ID3D11Resource), &m_BackBuffer);
	HRESULT DEBUGCODE = m_Device->CreateRenderTargetView(m_BackBuffer.Get(), nullptr, &m_RenderTarget);
	#if IS_DEBUG
		MB_EXCEPTION(DEBUGCODE);
	#endif
}

ID3D11Device* MafiaBar::Engine::Graphics::Graphics::Graphics::GetDevice() const 
{ 
	return m_Device.Get(); 
}

IDXGISwapChain* MafiaBar::Engine::Graphics::Graphics::Graphics::GetSwap() const 
{
	return m_Swap.Get(); 
}

ID3D11DeviceContext* MafiaBar::Engine::Graphics::Graphics::Graphics::GetContext() const 
{
	return m_Context.Get(); 
}

ID3D11RenderTargetView* MafiaBar::Engine::Graphics::Graphics::Graphics::GetRenderTarget() const 
{ 
	return m_RenderTarget.Get(); 
}

ID3D11DepthStencilState* MafiaBar::Engine::Graphics::Graphics::Graphics::GetDepthStencilState() const 
{ 
	return m_DepthStencilState.Get(); 
}

ID3D11DepthStencilView* MafiaBar::Engine::Graphics::Graphics::Graphics::GetDepthStencilView() const 
{ 
	return m_DepthStencilView.Get(); 
}

int MafiaBar::Engine::Graphics::Graphics::Graphics::GetWidth() const 
{
	return Width; 
}

int MafiaBar::Engine::Graphics::Graphics::Graphics::GetHeight() const 
{ 
	return Height; 
}

DirectX::SpriteBatch* MafiaBar::Engine::Graphics::Graphics::Graphics::GetSpriteBatch() const 
{ 
	return m_SpriteBatch.get(); 
}

DirectX::CommonStates* MafiaBar::Engine::Graphics::Graphics::Graphics::GetCommonStates() const
{
	return m_CommonStates.get();
}

const unsigned long MafiaBar::Engine::Graphics::Graphics::Graphics::GetGraphicCardMemorySize() const 
{ 
	return m_GraphicCardMemorySize; 
}

const char* MafiaBar::Engine::Graphics::Graphics::Graphics::GetGraphicCardDescription() const 
{ 
	return m_GraphicCardDescription; 
}

const bool MafiaBar::Engine::Graphics::Graphics::Graphics::GetVsyncBoolean() const 
{ 
	return m_Vsync; 
}

constexpr std::pair<const char*, unsigned long> MafiaBar::Engine::Graphics::Graphics::Graphics::GetGraphicCardInfo() const 
{ 
	return { m_GraphicCardDescription, m_GraphicCardMemorySize }; 
}
