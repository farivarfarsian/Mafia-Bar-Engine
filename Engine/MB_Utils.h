#pragma once
#include "Engine.h"

namespace MafiaBar
{
	class EXP_ENGINE Hotkey
	{
	public:
		static enum DefaultHotkeyIDs
		{
			ESC = 1,
			QUIT = 2
		};
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
		float Mark();
		float Peek() const;
		const char* GetCurrentDateAndTime();
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
	class EXP_ENGINE WindowDialogs
	{
	public:
		class FileOperations
		{
		public:
			static std::string SaveFileDialog(const char* filter, const HWND& owner = nullptr)
			{
				//Tempalte of Filters "All files\0*.*\0Source Files\0*.cpp\0"
				OPENFILENAMEA ofn;
				char fileName[MAX_PATH] = "";
				ZeroMemory(&ofn, sizeof(ofn));

				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = owner;
				ofn.lpstrFilter = filter;
				ofn.lpstrFile = fileName;
				ofn.nMaxFile = MAX_PATH;
				ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				ofn.lpstrDefExt = "";

				if (GetSaveFileNameA(&ofn) == TRUE)
				{
					std::string Filename = fileName;
					return Filename;
				}
				else { return "\0"; }
			}
			static std::string OpenFileDilog(const char* filter, const HWND& owner = nullptr)
			{
				//Tempalte of Filters "All files\0*.*\0Source Files\0*.cpp\0"
				OPENFILENAMEA ofn;
				char fileName[MAX_PATH] = "";
				ZeroMemory(&ofn, sizeof(ofn));

				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = owner;
				ofn.lpstrFilter = filter;
				ofn.lpstrFile = fileName;
				ofn.nMaxFile = MAX_PATH;
				ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				ofn.lpstrDefExt = "";

				if (GetOpenFileNameA(&ofn))
				{
					std::string Filename = fileName;
					return Filename;
				}
			}
		};
	};
}