#include "MafiaBarWString.h"

MafiaBar::MafiaBarWString::MafiaBarWString() : std::wstring() {}

MafiaBar::MafiaBarWString::MafiaBarWString(const wchar_t* buf) : std::wstring(buf) {}

MafiaBar::MafiaBarWString::MafiaBarWString(const std::wstring& buf) : std::wstring(buf) {}

std::string MafiaBar::MafiaBarWString::GetString() const
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> ConvertWString;
	return ConvertWString.to_bytes(*this);
}

std::wstring MafiaBar::MafiaBarWString::ToLowerCase()
{
	std::transform(begin(), end(), begin(), ::tolower);
	return (*this);
}

std::wstring MafiaBar::MafiaBarWString::ToUpperCase()
{
	std::transform(begin(), end(), begin(), ::toupper);
	return (*this);
}