#include "MafiaBarString.h"

MafiaBar::MafiaBarString::MafiaBarString() : std::string() {}

MafiaBar::MafiaBarString::MafiaBarString(const char* buf) : std::string(buf) {}

MafiaBar::MafiaBarString::MafiaBarString(const std::string& buf) : std::string(buf) {}

std::wstring MafiaBar::MafiaBarString::GetWString() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ConvertWString;
	return ConvertWString.from_bytes(*this);
}

std::string MafiaBar::MafiaBarString::ToLowerCase() 
{
	std::transform(begin(), end(), begin(), ::tolower);
	return *this;
}

std::string MafiaBar::MafiaBarString::ToUpperCase() 
{
	std::transform(begin(), end(), begin(), ::toupper);
	return *this;
}
