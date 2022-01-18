#pragma once
#include "pch.h"
#include <MB_Graphics.h>
#include <MB_Exception.h>
#include <MB_Keyboard.h>
#include <MB_Mouse.h>
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
		HRESULT hr;
		Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer = nullptr;
		graphics->GetSwap()->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);

		hr = D3DX11SaveTextureToFileA(graphics->GetContext(), backBuffer.Get(), D3DX11_IFF_JPG, "SCREENSHOT.JPG"); //This Function fails
		if (FAILED(hr)) { log.Message("Getting Screenshot", "Failed", 0, handle); }
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