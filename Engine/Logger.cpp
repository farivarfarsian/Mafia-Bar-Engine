#include "Logger.h"

void MafiaBar::Engine::Logger::Log(const char* Detail, const char* Value)
{
	LoggerStream.open("Mafia Bar Engine.log", std::fstream::app | std::fstream::out);
	if (LoggerStream.is_open() == true)
	{
		long long CurrentTime;
		time(&CurrentTime);
		LoggerStream << '[' << strtok(ctime(&CurrentTime), "\n") << " (Local Time)" << ']' << '\t' << Detail << ':' << '\t' << Value << '\n';
		LoggerStream.close();
	}
	else { Message("Logger Class Error Stream File", "We have some kind of problems to Access the Mafia Bar Engine.log", MB_ICONWARNING); }
}

void MafiaBar::Engine::Logger::LogEx(const char* Subject, const char* format, ...)
{
	LoggerStream.open("Mafia Bar Engine.log", std::ios::app | std::ios::out);
	char buffer[MAX_NAME_STRING];
	va_list args;
	va_start(args, format);

	vsprintf(buffer, format, args);
	if (LoggerStream.is_open() == true)
	{
		long long CurrentTime;
		time(&CurrentTime);
		LoggerStream << '[' << strtok(ctime(&CurrentTime), "\n") << " (Local Time)" << ']' << '\t' << Subject << ':' << '\t' << buffer << '\n';
		LoggerStream.close();
	}
	else { Message("Logger Class Error Stream File", "We have some kind of problems to Access the Mafia Bar Engine.log", MB_ICONWARNING); }


	va_end(args);
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
	if (MessageBoxMessages == IDABORT) { PostQuitMessage(0); }
	else if (MessageBoxMessages == IDRETRY) { /*Restart*/ }
}

int __stdcall MafiaBar::Engine::Logger::Message(const char* title, const char* message, UINT Type, HWND WindowHandle) noexcept { return MessageBoxA(WindowHandle, message, title, Type); }

int __stdcall MafiaBar::Engine::Logger::MessageEx(const char* title, UINT Type, HWND WindowHandle, const char* message, ...) noexcept
{
	char buffer[MAX_NAME_STRING * 2];

	va_list args;
	va_start(args, message);
	vsprintf(buffer, message, args);
	va_end(args);

	return MessageBoxA(WindowHandle, buffer, title, Type);
}

const char* MafiaBar::Engine::Logger::GetLoggerFileName() const { return LoggerName; }
