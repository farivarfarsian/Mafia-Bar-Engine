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

void MafiaBar::Console::CreateWIN32Console()
{
    AllocConsole(); FILE* fp;
    freopen_s(&fp, "CONIN$", "r", stdin);
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    SetConsoleTitleA("Mafia Bar Engine: Debug Console");
}

void MafiaBar::Console::CreateConsole(HWND ParentWindowHandle)
{
    #pragma message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")"  ": warning: " "Creating a Window as the child of ParentDirectX Window Doesn't Work well No idea why, Pls Fix")
    ConsoleHandle = CreateWindowExA(WS_EX_TRANSPARENT | WS_EX_CLIENTEDGE, "Edit", "\t\t\t\t\t\t\t\tMafia Bar Engine : Debug Console", WS_CHILD | WS_VISIBLE | ES_LEFT |
        ES_MULTILINE| ES_READONLY, 0, 620, 1199, 200, ParentWindowHandle, NULL, NULL, NULL);
    ChangeFont(8, "Segoe UI Light");
}

int MafiaBar::Console::GetConsoleTextLength() { return GetWindowTextLengthA(ConsoleHandle); }

char* MafiaBar::Console::GetAllConsoleText()
{
    int length = GetConsoleTextLength() + 1;
    char* message = (char*)alloca(length * sizeof(char));
    GetWindowTextA(ConsoleHandle, message, length);
    return message;
}

void MafiaBar::Console::Print(const std::string& Message)
{
    int TextLen = SendMessageA(ConsoleHandle, WM_GETTEXTLENGTH, 0, 0);
    SendMessageA(ConsoleHandle, EM_SETSEL, (WPARAM)TextLen, (LPARAM)TextLen);
    SendMessageA(ConsoleHandle, EM_REPLACESEL, FALSE, (LPARAM)Message.c_str());
}

HWND MafiaBar::Console::GetConsoleHandle() const { return ConsoleHandle; }

void MafiaBar::Console::ClearConsole() { SetWindowTextA(ConsoleHandle, "\0"); }

void MafiaBar::Console::ShowConsole() { ShowWindow(ConsoleHandle, SW_SHOW); }

void MafiaBar::Console::HideConsole() { ShowWindow(ConsoleHandle, SW_HIDE); }

void MafiaBar::Console::SetTextColor(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void MafiaBar::Console::ChangeFont(int Font_Size, const char* Font_Name)
{
    HFONT hFont = CreateFontA(0, Font_Size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, Font_Name);
    SendMessageA(ConsoleHandle, WM_SETFONT, (WPARAM)hFont, 0);
}

std::tuple<int, int, int> MafiaBar::Console::GetColors() const { return std::make_tuple(r, g, b); }
