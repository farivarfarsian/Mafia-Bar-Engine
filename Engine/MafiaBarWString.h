#pragma once
#include "Definitions.h"
#include "pch.h"
#include <codecvt>

namespace MafiaBar
{
	class MB_ENGINE_API MafiaBarWString : public std::wstring
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