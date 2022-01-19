#pragma once
#include "pch.h"
#include <Engine.h>

#include <MB_Utils.h>

class Window
{
public:
	MafiaBar::Keyboard keyboard;
	MafiaBar::Mouse mouse;
	MafiaBar::Console console;
	MafiaBar::Hotkey hotkey;
	MafiaBar::Logger log;
	MafiaBar::WindowDialogs windialogs;
	std::unique_ptr<MafiaBar::Graphics> graphics;
public:
	struct GENGW_Exceptions : public MafiaBar::Exceptions
	{
		GENGW_Exceptions(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TranslteErrorCodes(HRESULT hr) noexcept;
		std::string GetErrorString() const noexcept;
		HRESULT hr;
	};
public:
	Window() = default;
	Window(const char* WinTitle, int width, int height, bool fullscreen);
	std::optional<int> ProcessMessages();
	static LRESULT __stdcall WindowProcedureSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT __stdcall WindowProcedureThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void RegisterWindowClass();
	~Window();
public:
	enum Transparency
	{
		Nothing = 0x00,
		Half = 0xFF / 2,
		Full = 0xFF
	};
	void SetWindowTransparency(std::uint8_t Transperancy);
	void SetWindowAsOverlay();
	void AddMenus(HWND hwnd);
	BOOL CenterWindow(HWND hwndWindow);
	void ScreenShot() /* It doesn't work, pls fix */
	{		
		D3D11_TEXTURE2D_DESC desc{};
		HRESULT hr = S_OK;
		ID3D11Resource* pSurface = nullptr;
		ID3D11Texture2D* pTexture = nullptr;


		hr = graphics->GetSwap()->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pSurface));

		desc.ArraySize = 1u;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.Width = Width;
		desc.Height = Height;
		desc.MipLevels = 1u;
		desc.SampleDesc.Count = 1u;
		desc.SampleDesc.Quality = 0u;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET;
		desc.Usage = D3D11_USAGE_DEFAULT;


		hr = graphics->GetDevice()->CreateTexture2D(&desc, nullptr, &pTexture);
		if (pTexture)
		{
			graphics->GetContext()->ResolveSubresource(pTexture, 0, pSurface, 0, DXGI_FORMAT_R8G8B8A8_UNORM);
			hr = D3DX11SaveTextureToFileA(graphics->GetContext(), pTexture, D3DX11_IFF_BMP, "test.bmp");
			pTexture->Release();
		}
		pSurface->Release();
	}
public:
	HWND GetHandle() const { return handle; }
	HINSTANCE GetInstance() const { return hInstance; }
	DWORD GetProcessID() const { return ProcID; }
	int GetWindowWidth() const { return Width; }
	int GetWindowHeight() const { return Height; }
	bool GetFullscreenBoolean() const { return fullscreen; }
private:
	HWND handle = NULL;
	DWORD ProcID = GetCurrentProcessId();
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	int Width, Height;
	const char* AppName;
	bool fullscreen;
	HMENU WindowMenus;
};