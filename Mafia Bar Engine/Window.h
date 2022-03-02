#pragma once
#include <Engine.h>

#include <MB_Utils.h>

#include <Console.h>

#include "resource.h"

using MafiaBar::Engine::Engine;

extern class Window* window;

class Window final
{
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
	BOOL CenterWindow(HWND hwndWindow);
	void Restart();
	void Exit(int ExitCode); 
public:
	HWND GetHandle() const { return handle; }
	DWORD GetProcessID() const { return ProcessID; }
	HINSTANCE GetWinInstance() const { return hInstance; }
	int GetWindowWidth() const { return Width; }
	int GetWindowHeight() const { return Height; }
	bool GetFullscreenBoolean() const { return fullscreen; }
	bool GetFocusBoolean() const { return focus; }
	MafiaBar::Hotkey GetHotkey() const { return hotkey; }
	char* GetProgramFullPath() const
	{
	   static char pathtofile[MAX_PATH] {};
	   GetModuleFileNameA(hInstance, pathtofile, sizeof(pathtofile));
	   return pathtofile;
	}
private:	
	int Width, Height;
	const char* AppName;
	bool fullscreen, focus;
	HWND handle = NULL;
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	DWORD ProcessID = GetCurrentProcessId();
	MafiaBar::Hotkey hotkey;
};



