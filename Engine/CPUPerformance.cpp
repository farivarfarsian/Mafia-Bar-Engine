#include "CPUPerformance.h"

MafiaBar::Engine::Performance::CPUPerformance::CPUPerformance()
{
	PDH_STATUS pStatus = PdhOpenQuery(nullptr, 0, &m_QueryHandle);
	if (pStatus != ERROR_SUCCESS) { Engine::Get().GetException().Check(__FILE__, __FUNCSIG__, __LINE__, pStatus); }
	//set query object to poll all cpus in the system
	pStatus = PdhAddCounter(m_QueryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_CounterHandle);
	if (pStatus != ERROR_SUCCESS) { Engine::Get().GetException().Check(__FILE__, __FUNCSIG__, __LINE__, pStatus); }

	m_LastSampleTime = GetTickCount();
	m_CPUUsage = 0u;
}

MafiaBar::Engine::Performance::CPUPerformance::~CPUPerformance() { PdhCloseQuery(m_QueryHandle); }

void MafiaBar::Engine::Performance::CPUPerformance::Calculate()
{
	PDH_FMT_COUNTERVALUE value;
	if ((m_LastSampleTime + 1000) < GetTickCount())
	{
		m_LastSampleTime = GetTickCount();

		PdhCollectQueryData(m_QueryHandle);

		PdhGetFormattedCounterValue(m_CounterHandle, PDH_FMT_LONG, nullptr, &value);

		m_CPUUsage = value.longValue;
	}
}

constexpr int MafiaBar::Engine::Performance::CPUPerformance::GetCPUPercentage() const { return static_cast<int>(m_CPUUsage); }