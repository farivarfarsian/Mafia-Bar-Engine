#include "FPSCounter.h"

MafiaBar::Engine::Performance::FPSCounter::FPSCounter()
{
	QueryPerformanceCounter(&Start);
	QueryPerformanceFrequency(&Frequency);
}

void MafiaBar::Engine::Performance::FPSCounter::TheEnd()
{
	QueryPerformanceCounter(&End);

	CalculateCounts();
}

constexpr __int64 MafiaBar::Engine::Performance::FPSCounter::GetFPS() { return FPS.QuadPart = Frequency.QuadPart / Counts.QuadPart; }

constexpr __int64 MafiaBar::Engine::Performance::FPSCounter::GetSeconds() { return MS.QuadPart = ((1000 * Counts.QuadPart) / Frequency.QuadPart); }

void MafiaBar::Engine::Performance::FPSCounter::CalculateCounts()
{
	Counts.QuadPart = End.QuadPart - Start.QuadPart;
	Start = End;
}