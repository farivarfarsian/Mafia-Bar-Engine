#include "Utilities.h"

MafiaBar::Utilities::Time::Time(const char* Process_Describ)
    : start(std::chrono::high_resolution_clock::now()), label(Process_Describ)  
{ 
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

MafiaBar::Utilities::Time::Time() { last = std::chrono::steady_clock::now(); }

void MafiaBar::Utilities::Time::Start(const char* Process_Describ)
{
    start = std::chrono::high_resolution_clock::now();
    label = Process_Describ;
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

void MafiaBar::Utilities::Time::End()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    printf("The Procces: %s Took: %fms\n", label, ms);
}

float MafiaBar::Utilities::Time::Mark()
{
    const auto old = last;
    last = std::chrono::steady_clock::now();
    const std::chrono::duration<float> frameTime = last - old;
    return frameTime.count();
}

float MafiaBar::Utilities::Time::Peek() const { return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count(); }

const char* MafiaBar::Utilities::Time::GetCurrentDateAndTime()
{
    time_t rawtime;
    time(&rawtime);
    return ctime(&rawtime);
}

constexpr MB_ENGINE_API const DWORD MafiaBar::Utilities::GetProcessID(HWND Handle)
{
    if (Handle == NULL) { return GetCurrentProcessId(); }
    else
    {
        DWORD ProcessID = 0;
        GetWindowThreadProcessId(Handle, &ProcessID);
        return ProcessID;
    }
}

MB_ENGINE_API char* MafiaBar::Utilities::GetProgramFullPath(HINSTANCE hInstance)
{
    static char pathtofile[MAX_PATH]{};
    GetModuleFileNameA(hInstance, pathtofile, sizeof(pathtofile));
    return pathtofile;
}

MB_ENGINE_API void MafiaBar::Utilities::SetWindowTransparency(HWND Handle, uint8_t Transperancy)
{
    long wAttr = GetWindowLong(Handle, GWL_EXSTYLE);
    SetWindowLong(Handle, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
    SetLayeredWindowAttributes(Handle, 0, Transperancy, 0x02);
}

MB_ENGINE_API void MafiaBar::Utilities::SetWindowAsOverlay(HWND Handle) { ::SetWindowPos(Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); }

MB_ENGINE_API BOOL MafiaBar::Utilities::CenterWindow(HWND Handle, int Width, int Height)
{
    if (Width == 0 && Height == 0)
    {
        RECT rect;
        if (GetWindowRect(Handle, &rect) == TRUE)
        {
            Width = rect.right - rect.left;
            Height = rect.bottom - rect.top;
        }
    }

    int CenterScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - Width / 2;
    int CenterScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - Height / 2;

    RECT wr{};
    wr.left = CenterScreenX;
    wr.top = CenterScreenY;
    wr.right = wr.left + Width;
    wr.bottom = wr.top + Height;
    if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false) == false) { return false; }

    if (MoveWindow(Handle, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, true) == false) { return false; }

    return true;
}
