#pragma once
#include "Engine.h"
namespace MafiaBar
{
	class EXP_ENGINE Hotkey
	{
	public:
		bool RegisterHotKey(const HWND& handle, int hotkey_id, int fsModifiers, int vk);
		bool UnregisterHotKey(const HWND& handle, int hotkey_id);
		int GetHotkeyID() const { return HotkeyID; }
	private:
		int HotkeyID = 0;
	};
	class EXP_ENGINE WindowRegistery
	{
	public:
		bool RegistryWrite(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value);
		char* RegistryRead(LPCTSTR subkey, LPCTSTR name, DWORD type);
	};
	class EXP_ENGINE Time
	{
    public:
		Time(const char* Process_Describ);
		Time() = default;
		void End();
		float Mark()
		{
			const auto old = last;
			last = std::chrono::steady_clock::now();
			const std::chrono::duration<float> frameTime = last - old;
			return frameTime.count();
		}
		float Peek() const
		{
			return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
		}
    private:
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::duration<double> duration;
        const char* label;
		std::chrono::steady_clock::time_point last;
	};
    class EXP_ENGINE Console
    {
	//Undefing Useless Microsoft Macros in Windows.h
		#undef GetConsoleTitle
    public:
        Console(const char* cmdcolor = 0);
        HWND GetConsoleHandle() const;
        std::string GetConsoleTitle() const;
    private:
        std::string ConsoleTitle = "Mafia Bar Engine: Debug Console";
		int GetColumnWidthConsole();
    };
}