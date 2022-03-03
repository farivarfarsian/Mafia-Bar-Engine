#pragma once
#include "Definitions.h"
#include <Windows.h>
#include <filesystem>

namespace MafiaBar
{
	namespace Engine
	{
		namespace filesystem
		{
			#undef CreateDirectory
			#undef DeleteFile
			#undef CopyFile
			#undef MoveFile
			MB_ENGINE_API bool CreateDirectory(const char* DirectoryPath);
			MB_ENGINE_API bool ExistenceDirectory(const char* DirectoryName);
			MB_ENGINE_API bool DeleteDirectory(const char* DirectoryPath, bool Recursively = false);
			MB_ENGINE_API uintmax_t GetFileSize(const char* FilePath);
			MB_ENGINE_API std::string GetFileName(const char* FilePath);
			MB_ENGINE_API std::string GetFileExtension(const char* FilePath);
			MB_ENGINE_API short DeleteFile(const char* FilePath);
			MB_ENGINE_API bool CopyFile(const char* SourceFilePath, const char* DestinationFilePath);
			MB_ENGINE_API bool MoveFile(const char* SourceFilePath, const char* DestinationFilePath);
			MB_ENGINE_API bool ExistenceFile(const char* FilePath);
		}
	}
}
