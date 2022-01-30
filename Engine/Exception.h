#pragma once
#include "Engine.h"

namespace MafiaBar
{
	class EXP_ENGINE Exceptions : public std::exception
	{
	public:
		Exceptions(int line, const char* file) noexcept
			: line(line), file(file)
		{}
		const char* what() const noexcept;
		virtual const char* GetType() const noexcept;
		std::string GetOriginString() const noexcept;
	protected:
		int line;
		std::string file;
	protected:
		mutable std::string whatBuffer;
	};
}


