#pragma once
#include "def.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Performance
		{
			class MB_ENGINE_API CPUPerformance
			{
			public:
				CPUPerformance();
				CPUPerformance(const CPUPerformance&) = delete;
				CPUPerformance& operator=(const CPUPerformance&) = delete;
				~CPUPerformance() = default;
				double GetCPUPercentage();
			private:
				ULARGE_INTEGER LastCPU, LastSysCPU, LastUserCPU;
				int NumberOfProcessors;
				HANDLE Process;	
			}; //The Old Version had some bugs, New Version has been scrapped from: https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process here. This New Version still has some bugs because in low cpu percentages it seems that the value is zero but it's not.
		}
	}
}