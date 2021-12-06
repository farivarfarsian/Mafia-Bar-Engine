#pragma once
#include "pch.h"
#include <MB_Graphics.h>
#include "../Engine/MB_Exception.h"
#include "../Engine/MB_Keyboard.h" 
#include "../Engine/MB_Mouse.h"

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Keyboard keyboard;
	Mouse mouse;
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
	enum Transparency
	{
		Nothing = 0x00,
		Half = 0xFF / 2,
		Full = 0xFF
	};
	Window() = default;
	Window(const char* WinTitle, int width, int height);
	std::optional<int> ProcessMessages();
	void RegisterWindowClass();
	~Window();
	void SetWindowTransparency(std::uint8_t Transperancy);
	void SetWindowAsOverlay();
	void SetTitle(const std::string& title);
	HWND GetHandle() const { return handle; }
	HINSTANCE GetInstance() const { return hInstance; }
	DWORD GetProcessID() const { return ProcID; }
public:
	MafiaBar::Graphics& GetGraphics();
private:
	HWND handle = NULL;
	DWORD ProcID = GetCurrentProcessId();
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	std::unique_ptr<MafiaBar::Graphics> m_Graphics;
};