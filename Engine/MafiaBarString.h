#pragma once
#include "Definitions.h"
#include "pch.h"
#include <codecvt>

namespace MafiaBar
{
	class MB_ENGINE_API MafiaBarString : public std::string
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