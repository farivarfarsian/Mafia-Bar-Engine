#pragma once
#include "../Mafia Bar Engine/pch.h"
/*
	-----------------Logger.h By Mafia Bar------------------
	-----This File is For Sending/Creating LOG Messages-----
*/


/*
*	Mafia Bar Engine Toolkit Compiler Error Messages
* Just use #define ERRORMESSAGE 1
* And Then Whatever Text you Want in LOG Like:
* #define LOG "This is a Compiler Error"
*	Mafia Bar Engine Toolkit Compiler Error Messages
*	Mafia Bar Engine Toolkit Compiler Warning Messages
* Just use #define WARNMESSAGE 1
* And Then Whatever Text You Want in LOG Like:
* #define LOG "This is a Compiler Warning Message
* Mafia Bar Engine Toolkit Compiler Warning Messages
*/

#if WARNMESSAGE == 1
#pragma message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")"  ": warning: " LOG)
#else
#define WARNMESSAGE 0
#endif

#if ERRORMESSAGE == 1
#pragma message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")"  ": error: " LOG)
#else
#define ERRORMESSAGE 0
#endif

namespace MafiaBar
{
	class Logger
	{
	public:
		void LogToFile(const char* detail, const char* value = "\0")
		{
			LoggerStream.open("Mafia Bar Engine.log", std::ios::app | std::ios::out);
			if (LoggerStream.is_open())
			{
				long long CurrentTime;
				time(&CurrentTime);
				LoggerStream << '[' << strtok(ctime(&CurrentTime), "\n") << ']' << '\t' << detail << ':' << '\t' << value << '\n';
				LoggerStream.close();
			}
			else { Message("Logger Class Error Stream File", "We have some kind of problems to Access the Mafia Bar Engine.log", MB_ICONWARNING); }
		}
		void Message(const char* title, const char* message, UINT Type, HWND WindowHandle = NULL) { MessageBoxA(WindowHandle, message, title, Type); }
	public:
		const char* GetFileName() const { return MafiaBarFileLogName; }
	private:;
		std::fstream LoggerStream;
		const char* MafiaBarFileLogName = "Mafia_Bar_Engine.log";
	};
}
