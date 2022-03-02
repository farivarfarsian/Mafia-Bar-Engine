#include "Exception.h"

MafiaBar::Engine::Exception::~Exception() noexcept { LocalFree(Description); }

MafiaBar::Engine::Exception::Exception(const char* File, const char* Function, int Line, DebugCode DebugCode) noexcept
{
	if (DebugCode == S_OK) { return; }
	DC = DebugCode;
	StringStream << "[Error Code] 0x" << std::hex << DebugCode << '\n'
		<< "[Description] " << what()
		<< "[File]" << File << '\n'
		<< "[Function] " << Function << '\n'
		<< "[Line] " << std::to_string(Line) << '\n';
	Throw(StringStream.str().c_str());
}

void MafiaBar::Engine::Exception::Check(const char* File, const char* Function, int Line, DebugCode DebugCode) noexcept 
{
	if (DebugCode == S_OK) { return; }
	DC = DebugCode;
	StringStream << "[Error Code] 0x" << std::hex << DebugCode << '\n'
		<< "[Description] " << what()
		<< "[File]" << File << '\n'
		<< "[Function] " << Function << '\n'
		<< "[Line] " << std::to_string(Line) << '\n';
	Throw(StringStream.str().c_str());
}

void MafiaBar::Engine::Exception::Throw(const char* Subject)
{
	int MessageR = MessageBoxA(FindWindowA(NULL, "Mafia Bar Engine"), Subject, GetType(), MB_ABORTRETRYIGNORE | MB_ICONERROR);
	if (MessageR == IDRETRY) {}
	else if (MessageR == IDABORT) { PostQuitMessage(-1); }
}

const char* MafiaBar::Engine::Exception::what() const noexcept
{
	FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		DC,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&Description,
		0,
		NULL);
	if (this->Description != NULL) { return Description; }
	else { return "Formating the code failled\n"; }
}

MafiaBar::Engine::GraphicException::GraphicException(const char* File, const char* Function, int Line, DebugCode DebugCode) noexcept : Exception(File, Function, Line, DebugCode) { }

const char* MafiaBar::Engine::GraphicException::GetType() const noexcept { return "Mafia Bar Engine Graphic Exception"; }