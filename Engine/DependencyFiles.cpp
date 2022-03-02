#include "DependencyFiles.h"

constexpr void MafiaBar::Engine::DependencyFiles::AddDependencyFile(const char* FileName) { DependencyFileNames.PushBack(FileName); }

inline void MafiaBar::Engine::DependencyFiles::DeleteLastDependencyFile(void) { DependencyFileNames.PopBack(); }

constexpr void MafiaBar::Engine::DependencyFiles::Check(void)
{
	struct stat buffer;
	for (const char* value : DependencyFileNames)
	{
		if ((stat(value, &buffer) == 0) == false)
		{
			Engine::Get().GetLogger().LogEx("Dependency Files", "The File %s is needed but doesn't exist", value);
			Engine::Get().GetLogger().MessageEx("Dependency Files", MB_ABORTRETRYIGNORE | MB_ICONERROR, FindWindowA(NULL, "Mafia Bar Engine"), "The File %s is needed but doesn't exist", value);
		}
	}
}