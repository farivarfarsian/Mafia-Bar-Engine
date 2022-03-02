#pragma once
#include "Definitions.h"
#include "pch.h"

namespace MafiaBar
{
	class MB_ENGINE_API Hotkey
	{
	public:
		enum DefaultHotkeyIDs
		{
			ESC = 1,
			QUIT = 2,
			FULLSCREEN = 3
		};
		bool RegisterHotKey(const HWND& handle, int hotkey_id, int fsModifiers, int vk);
		bool UnregisterHotKey(const HWND& handle, int hotkey_id);
		int GetHotkeyID() const { return HotkeyID; }
	private:
		int HotkeyID = 0;
	};
	class MB_ENGINE_API Time
	{
    public:
		Time(const char* Process_Describ);
		Time();
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
	class MB_ENGINE_API WindowDialogs
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