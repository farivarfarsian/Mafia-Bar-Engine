#pragma once
#include "Engine.h"
#include <codecvt>

namespace MafiaBar
{
	class EXP_ENGINE MafiaBarString : public std::string
	{
	public:
		MafiaBarString();
		MafiaBarString(const char* buf);
		MafiaBarString(const std::string& buf);
		std::wstring GetWString() const;
		std::string ToLowerCase();
		std::string ToUpperCase();
	};
}