#pragma once
#include "Engine.h"
#include <codecvt>

namespace MafiaBar
{
	class EXP_ENGINE MafiaBarWString : public std::wstring
	{
	public:
		MafiaBarWString();
		MafiaBarWString(const wchar_t* buf);
		MafiaBarWString(const std::wstring& buf);
		std::string GetString() const;
		std::wstring ToLowerCase();
		std::wstring ToUpperCase();
	};
}