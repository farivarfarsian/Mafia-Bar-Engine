#include "FPSCounter.h"

MafiaBar::Engine::Graphics::FPSCounter::FPSCounter()
{
	QueryPerformanceCounter(&Start);
	QueryPerformanceFrequency(&Frequency);
}

void MafiaBar::Engine::Graphics::FPSCounter::TheEnd()
{
	QueryPerformanceCounter(&End);

	CalculateCounts();
}

__int64 MafiaBar::Engine::Graphics::FPSCounter::GetFPS() { return FPS.QuadPart = Frequency.QuadPart / Counts.QuadPart; }

__int64 MafiaBar::Engine::Graphics::FPSCounter::GetSeconds() { return MS.QuadPart = ((1000 * Counts.QuadPart) / Frequency.QuadPart); }

void MafiaBar::Engine::Graphics::FPSCounter::CalculateCounts()
{
	Counts.QuadPart = End.QuadPart - Start.QuadPart;
	Start = End;
}