#pragma once
#include "Definitions.h"
#include "pch.h"
#include "MafiaBarString.h"

namespace MafiaBar
{
	class MB_ENGINE_API MafiaBarFileStream : public std::fstream
	{
	public:
		MafiaBarFileStream();
		MafiaBarFileStream(const MafiaBarFileStream&) = delete;
		explicit MafiaBarFileStream(const char* FileName, std::ios_base::openmode mode);
		explicit MafiaBarFileStream(const MafiaBar::MafiaBarString& FileName, std::ios_base::openmode mode);
		static bool existence_of_a_file(const char* FilePath);
		static bool existence_of_a_file(const wchar_t* FilePath);
	public: //Binary Operation Functions
		void WriteBinary()
		{

		}
		void ReadInt32Binary()
		{

		}
	public:
		//Get The File Path.
		MafiaBarString GetFileName();
	private:
		MafiaBar::MafiaBarString Filename;
	};
}
