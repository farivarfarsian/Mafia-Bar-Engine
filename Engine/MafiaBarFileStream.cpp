#include "MafiaBarFileStream.h"

MafiaBar::MafiaBarFileStream::MafiaBarFileStream() : std::fstream() {}

MafiaBar::MafiaBarFileStream::MafiaBarFileStream(const char* FileName, std::ios_base::openmode mode) : std::fstream(FileName, mode), Filename(FileName) {}

MafiaBar::MafiaBarFileStream::MafiaBarFileStream(const MafiaBar::MafiaBarString& FileName, std::ios_base::openmode mode) : std::fstream(FileName, mode), Filename(FileName) {}

bool MafiaBar::MafiaBarFileStream::existence_of_a_file(const char* FilePath)
{
	struct stat buffer;
	return (stat(FilePath, &buffer) == 0);
}

MafiaBar::MafiaBarString MafiaBar::MafiaBarFileStream::GetFileName() { return Filename; }
