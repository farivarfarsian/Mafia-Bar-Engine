#pragma once
#include "pch.h"
#include <MB_Graphics.h>
#include <MB_Exception.h>
#include <MB_Keyboard.h>
#include <MB_Mouse.h>
#include <MB_Utils.h>


LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

class Window
{
public:
	Keyboard keyboard;
	Mouse mouse;
	MafiaBar::Console console;
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
	Window(const char* WinTitle, int width, int height);
	std::optional<int> ProcessMessages();
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
	BOOL CenterWindow(HWND hwndWindow);
public:
	HWND GetHandle() const { return handle; }
	HINSTANCE GetInstance() const { return hInstance; }
	DWORD GetProcessID() const { return ProcID; }
private:
	HWND handle = NULL;
	DWORD ProcID = GetCurrentProcessId();
	HINSTANCE hInstance = GetModuleHandleA(NULL);
};