#pragma once
#include "../Mafia Bar Engine/pch.h"

	class Exceptions : public std::exception
	{
	public:
		Exceptions(int line, const char* file) noexcept
			: line(line), file(file)
		{}
		const char* what() const noexcept
		{
			std::ostringstream oss;
			oss << GetType() << std::endl << GetOriginString();
			whatBuffer = oss.str(); //For Not Losing Date
			return whatBuffer.c_str();
		}

		virtual const char* GetType() const noexcept
		{
			return "Mafia Bar Engine Exceptions";
		}

		std::string GetOriginString() const noexcept
		{
			std::ostringstream oss;
			oss << " [File] " << file << '\n' << " [Line] " << line;
			return oss.str();

		}
		int line;
		std::string file;
	protected:
		mutable std::string whatBuffer;
	};

