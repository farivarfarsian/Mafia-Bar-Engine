#pragma once
/*
		-----------------Logger.h------------------
	-----This File is For Sending/Creating LOG Messages-----
*/
#include "Definitions.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Engine
	{	
		class MB_ENGINE_API Logger
		{
		public:
			Logger() = default;
			~Logger() = default;
			void Log(const char* Detail, const char* Value);
			void LogEx(const char* Subject, const char* format, ...);
			static int __stdcall Message(const char* title, const char* message, UINT Type, HWND WindowHandle = FindWindowA(NULL, "Mafia Bar Engine")) noexcept;
			static int __stdcall MessageEx(const char* title, UINT Type, HWND WindowHandle, const char* message, ...) noexcept;
			static void FetalError(const char* Description, const char* File, const char* Function, int Line);
			const char* GetLoggerFileName() const;
		private:
			std::ofstream LoggerStream;
			const char* LoggerName = "Mafia Bar Engine.log";
		};
	}
}