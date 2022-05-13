#pragma once
#include "def.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Performance
		{
			class MB_ENGINE_API FPSCounter
			{
			public:
				FPSCounter();
				void TheEnd();
				constexpr __int64 GetFPS();
				constexpr __int64 GetSeconds();
			private:
				LARGE_INTEGER Start, End, Counts, Frequency, FPS, MS;
				void CalculateCounts();
			};
		}
	}
}
