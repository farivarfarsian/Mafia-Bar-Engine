#pragma once
#include "Definitions.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Utilities
	{
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

		MB_ENGINE_API constexpr const DWORD GetProcessID(HWND Handle = NULL);

		MB_ENGINE_API char* GetProgramFullPath(HINSTANCE hInstance);

		MB_ENGINE_API void SetWindowTransparency(HWND Handle, uint8_t Transperancy);

		MB_ENGINE_API void SetWindowAsOverlay(HWND Handle);

		MB_ENGINE_API BOOL CenterWindow(HWND Handle, int Width = 0, int Height = 0);

		enum WindowTransparency
		{
			Nothing = 0x00,
			Half = 0xFF / 2,
			Full = 0xFF
		};
	}
}