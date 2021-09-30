#pragma once
#include "pch.h"
#include "../Engine Toolkit/Exceptions.h"
#include "../Engine Toolkit/Keyboard.h" 
#include "../Engine Toolkit/Mouse.h"
#include "../Engine Toolkit/Engine_Toolkit.h"


LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

class RenderWindow
{
public:
	Keyboard keyboard;
	Mouse mouse;
public:
	struct GENGW_Exceptions : public Exceptions
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
	WCHAR WindowClass[MAX_NAME_STRING] = L"Mafia Bar";
	WCHAR WindowTitle[MAX_NAME_STRING] = L"Mafia Bar Engine";
	bool Initialize(HINSTANCE hInstance, int width, int height);
	bool ProcessMessages();
	~RenderWindow();

	static void SetWindowTransparency(HWND hwnd, std::uint8_t Transperancy)
	{
		long wAttr = GetWindowLong(hwnd, GWL_EXSTYLE);
		SetWindowLong(hwnd, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwnd, 0, Transperancy, 0x02);
	}
	static void SetWindowAsOverlay(const HWND& hwnd)
	{
		::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	}
	HWND handle = NULL;
	DWORD ProcID;
	HINSTANCE hInstance = NULL;
	void RegisterWindowClass();
};