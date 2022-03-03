#include "FileSystem.h"

bool MafiaBar::Engine::filesystem::CreateDirectory(const char* DirectoryPath) { return std::filesystem::create_directory(DirectoryPath); }

bool MafiaBar::Engine::filesystem::ExistenceDirectory(const char* DirectoryName)
{
	DWORD ftyp = ::GetFileAttributesA(DirectoryName);
	if (ftyp == INVALID_FILE_ATTRIBUTES) { return false; }
	else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) { return true; }
	return false;
}

bool MafiaBar::Engine::filesystem::DeleteDirectory(const char* DirectoryPath, bool Recursively)
{
	if (ExistenceDirectory(DirectoryPath) == false) { return false; }
	if (Recursively == true) { return std::filesystem::remove_all(DirectoryPath); }
	else if (Recursively == false) { return std::filesystem::remove(DirectoryPath); }
}

uintmax_t MafiaBar::Engine::filesystem::GetFileSize(const char* FilePath) { return std::filesystem::file_size(FilePath); }

std::string MafiaBar::Engine::filesystem::GetFileName(const char* FilePath) { return std::filesystem::path(FilePath).stem().string(); }

std::string MafiaBar::Engine::filesystem::GetFileExtension(const char* FilePath) { return std::filesystem::path(FilePath).extension().string(); }

short MafiaBar::Engine::filesystem::DeleteFile(const char* FilePath) { return DeleteFileA(FilePath); }

bool MafiaBar::Engine::filesystem::CopyFile(const char* SourceFilePath, const char* DestinationFilePath) { return std::filesystem::copy_file(SourceFilePath, DestinationFilePath); }

bool MafiaBar::Engine::filesystem::MoveFile(const char* SourceFilePath, const char* DestinationFilePath) { return MoveFileA(SourceFilePath, DestinationFilePath); }

bool MafiaBar::Engine::filesystem::ExistenceFile(const char* FilePath) 
{
	struct stat buffer;
	return (stat(FilePath, &buffer) == 0);
}
