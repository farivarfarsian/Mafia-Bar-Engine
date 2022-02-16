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
		class EXP_ENGINE Logger
		{
		public:
			Logger() = default;
			void Log(const char* Detail, const char* Value = "\0");
			static void FetalError(const char* Description, const char* File, const char* Function, int Line);
			static int Message(const char* title, const char* message, UINT Type, HWND WindowHandle = FindWindowA(NULL, "Mafia Bar Engine"));
			const char* GetLoggerFileName() const;
		private:
			std::fstream LoggerStream;
			const char* LoggerName = "Mafia Bar Engine.log";
		};
	}
}