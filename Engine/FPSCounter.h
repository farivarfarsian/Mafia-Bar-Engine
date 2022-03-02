#pragma once
#include "Definitions.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Graphics
		{
			class MB_ENGINE_API FPSCounter
			{
			public:
				FPSCounter();
				void TheEnd();
				__int64 GetFPS();
				__int64 GetSeconds();
			private:
				LARGE_INTEGER Start, End, Counts, Frequency, FPS, MS;
				void CalculateCounts();
			};
		}
	}
}
