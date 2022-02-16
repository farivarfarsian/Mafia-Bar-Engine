#include "Logger.h"

void MafiaBar::Engine::Logger::Log(const char* Detail, const char* Value)
{
	LoggerStream.open(LoggerName, std::ios::app | std::ios::out);
	if (LoggerStream.is_open() == true)
	{
		long long CurrentTime;
		time(&CurrentTime);
		LoggerStream << '[' << strtok(ctime(&CurrentTime), "\n") << ']' << '\t' << Detail << ':' << '\t' << Value << '\n';
		LoggerStream.close();
	}
	else { Message("Logger Class Error Stream File", "We have some kind of problems to Access the Mafia Bar Engine.log", MB_ICONWARNING); }
}

void MafiaBar::Engine::Logger::FetalError(const char* Description, const char* File, const char* Function, int Line)
{
	std::stringstream DecriptionMessage;
	DecriptionMessage << "Mafia Bar Engine Fetal Error\n"
		<< "[Description] " << Description << '\n'
		<< "[File] " << File << '\n'
		<< "[Function] " << Function << '\n'
		<< "[Line] " << Line;

	int MessageBoxMessages = Message("Mafia Bar Engine", DecriptionMessage.str().c_str(), MB_ABORTRETRYIGNORE | MB_ICONERROR);
	//Try to replace with window object restart function
	if (MessageBoxMessages == IDABORT) { PostQuitMessage(0); }
	if (MessageBoxMessages == IDRETRY)
	{
		ShellExecuteA(FindWindowA(NULL, "Mafia Bar Engine"), "open", "Mafia Bar Engine.exe", NULL, NULL, SW_RESTORE);
		PostQuitMessage(0);
		ExitProcess(0);
	}
}

int MafiaBar::Engine::Logger::Message(const char* title, const char* message, UINT Type, HWND WindowHandle) { return MessageBoxA(WindowHandle, message, title, Type); }

const char* MafiaBar::Engine::Logger::GetLoggerFileName() const { return LoggerName; }
