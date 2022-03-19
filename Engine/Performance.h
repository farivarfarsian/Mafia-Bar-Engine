#pragma once

#include "CPUPerformance.h"

#include "FPSCounter.h"

#ifdef PERFORMANCE_OBJECT
namespace MafiaBar
{
	namespace Engine
	{
		namespace Performance
		{
			static CPUPerformance CPU;
			static FPSCounter FPS;
		}
	}
}
#endif //PERFORMANCE_OBJECT