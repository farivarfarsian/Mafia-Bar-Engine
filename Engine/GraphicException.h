#pragma once
#include "Engine.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class EXP_ENGINE GraphicException
			{
			public:
				GraphicException(const char* File, const char* Function, int Line, DebugCode debugcode)
				{
					Logger log;
					if (debugcode == S_OK)
					{
						//StringStream << "Function: " << Function << " At Line of " << Line << " In the File of " << File << " Have Succeeded With Graphic Operations.";
						//log.LogToFile(GetType(), StringStream.str().c_str());
					}
					else
					{
						FormatMessageA(
							FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
							NULL,
							debugcode,
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
							(LPSTR)&Description,
							0,
							NULL);
						
						if (NULL != Description)
						{
							StringStream << GetType() << '\n'
								<< "[Error Code] " << "0x" << std::hex << debugcode << '\n'
								<< "[Description] " << Description
								<< "[File] " << File << '\n'
								<< "[Function] " << Function << '\n'
								<< "[Line] " << std::to_string(Line);

							int MessageBoxMessages = Logger::Message("Mafia Bar Engine", StringStream.str().c_str(), MB_ABORTRETRYIGNORE | MB_ICONERROR);
							//Try to replace with window object restart function
							if (MessageBoxMessages == IDABORT) { PostQuitMessage(0); }
							if (MessageBoxMessages == IDRETRY)
							{
								log.Log("Mafia Bar Engine", "The Application Have Restarted");
								ShellExecuteA(FindWindowA(NULL, "Mafia Bar Engine"), "open", "Mafia Bar Engine.exe", NULL, NULL, SW_RESTORE);
								PostQuitMessage(0);
								ExitProcess(0);
							}


							LocalFree(Description);
							Description = NULL;
						}
						else
						{
							StringStream << GetType() << '\n'
								<< "[Error Code] " << "0x" << std::hex << debugcode << '\n'
								<< "[Description] " << "Unknown Error Code! \n"
								<< "[File] " << File << '\n'
								<< "[Function] " << Function << '\n'
								<< "[Line] " << std::to_string(Line);

							Logger::Message("Mafia Bar Engine", StringStream.str().c_str(), MB_ICONERROR);
						}
					}
				}
				GraphicException(const GraphicException&) = delete;
				GraphicException& operator=(const GraphicException&) = delete;
				~GraphicException() = default;
				const char* GetType() { return "Mafia Bar Engine Graphic Exception"; }
			private:			
				std::stringstream StringStream;
				LPSTR Description = NULL;
			};
		}
	}
}
