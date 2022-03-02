#include "MB_Utils.h"

bool MafiaBar::Hotkey::RegisterHotKey(const HWND& handle, int hotkey_id, int fsModifiers, int vk)
{
    HotkeyID = hotkey_id;
    return ::RegisterHotKey(handle, hotkey_id, fsModifiers, vk);
}

bool MafiaBar::Hotkey::UnregisterHotKey(const HWND& handle, int hotkey_id) { return ::UnregisterHotKey(handle, hotkey_id); }


MafiaBar::Time::Time(const char* Process_Describ)
    : start(std::chrono::high_resolution_clock::now()), label(Process_Describ)  
{ 
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

MafiaBar::Time::Time() { last = std::chrono::steady_clock::now(); }

void MafiaBar::Time::Start(const char* Process_Describ)
{
    start = std::chrono::high_resolution_clock::now();
    label = Process_Describ;
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

void MafiaBar::Time::End()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    printf("The Procces: %s Took: %fms\n", label, ms);
}

float MafiaBar::Time::Mark() 
{
    const auto old = last;
    last = std::chrono::steady_clock::now();
    const std::chrono::duration<float> frameTime = last - old;
    return frameTime.count();
}

float MafiaBar::Time::Peek() const { return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count(); }

const char* MafiaBar::Time::GetCurrentDateAndTime()
{
    time_t rawtime;
    time(&rawtime);
    return ctime(&rawtime);
}
