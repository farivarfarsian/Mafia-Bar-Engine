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
		void Start(const char* Process_Describ);
		void End();
	public:
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
	public:
		Console() = default;
		void CreateWIN32Console();
		void CreateConsole(HWND ParentWindowHandle);
		void Print(const std::string& Message);
		void ClearConsole();
		void ShowConsole();
		void HideConsole();
		void SetTextColor(int r, int g, int b);
		void ChangeFont(int Font_Size, const char* Font_Name);
	public:
		int GetConsoleTextLength();
		char* GetAllConsoleText();
		HWND GetConsoleHandle() const;
		std::tuple<int, int, int> GetColors() const;
    private:
		HWND ConsoleHandle = nullptr;
		int r = 255, g = 255, b = 255;
    };
}