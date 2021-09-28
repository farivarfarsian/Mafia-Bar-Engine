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

namespace Engine //Engine Namspace
{
	class EXP_ENGINE Logger //Logger Class
	{
	public:
		static void  LiveLog(const char* message) //Throwing MessageBox's
		{
			MessageBoxA(NULL, message, 0, 0);
		}
		template<typename T>
		static void StaticLog(const char* details, T Value) //Writing Anything You Want into Mafia_Bar_Engine.log
		{
			std::ofstream StreamW("Mafia_Bar_Engine.log", std::ios::app);
			StreamW << "[" << __DATE__ << ' ' << __TIME__ << "]" << "\t" << details << ':' << "\t" << Value << std::endl;
			StreamW.close();
		}
	};
}
