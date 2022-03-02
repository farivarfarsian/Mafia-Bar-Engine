#pragma once
#include "Engine.h"

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API DependencyFiles
		{
		public:
			DependencyFiles() = default;
			~DependencyFiles() = default;
			constexpr void AddDependencyFile(const char* FileName);
			inline void DeleteLastDependencyFile(void);
			constexpr void Check(void);
		private:
			MafiaBar::SDK::VirtualVector<C_String> DependencyFileNames; //Virtual Allocation used because maybe the dependency file count is really high so it's better to not allocate a lot of memory on Heap
		};
	}
}