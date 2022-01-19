#include "Exception.h"

const char* MafiaBar::Exceptions::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str(); //For Not Losing Date
	return whatBuffer.c_str();
}

const char* MafiaBar::Exceptions::GetType() const noexcept { return "Mafia Bar Engine Exceptions"; }

std::string MafiaBar::Exceptions::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << " [File] " << file << '\n' << " [Line] " << line;
	return oss.str();
}
