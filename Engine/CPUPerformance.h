#pragma once
#include "Definitions.h"
#include "Engine.h"

#include <Pdh.h>
LINK_LIBRARY("pdh.lib");

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
				~CPUPerformance();
				void Calculate();
				constexpr int GetCPUPercentage() const;
			private:
				HQUERY m_QueryHandle;
				HCOUNTER m_CounterHandle;
				unsigned long m_LastSampleTime;
				unsigned long m_CPUUsage;
			};
		}
	}
}