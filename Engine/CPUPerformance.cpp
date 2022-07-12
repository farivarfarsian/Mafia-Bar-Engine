#include "CPUPerformance.h"

MafiaBar::Engine::Performance::CPUPerformance::CPUPerformance()
{
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    NumberOfProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&LastCPU, &ftime, sizeof(FILETIME));

    Process = GetCurrentProcess();
    GetProcessTimes(Process, &ftime, &ftime, &fsys, &fuser);
    memcpy(&LastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&LastUserCPU, &fuser, sizeof(FILETIME));
}

double MafiaBar::Engine::Performance::CPUPerformance::GetCPUPercentage()
{
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(Process, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - LastSysCPU.QuadPart) +
        (user.QuadPart - LastUserCPU.QuadPart);
    percent /= (now.QuadPart - LastCPU.QuadPart);
    percent /= NumberOfProcessors;
    LastCPU = now;
    LastUserCPU = user;
    LastSysCPU = sys;

    return percent * 100;
}