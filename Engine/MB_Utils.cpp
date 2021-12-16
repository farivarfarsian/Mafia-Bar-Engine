#include "MB_Utils.h"

bool MafiaBar::Hotkey::RegisterHotKey(const HWND& handle, int hotkey_id, int fsModifiers, int vk)
{
    HotkeyID = hotkey_id;
    return ::RegisterHotKey(handle, hotkey_id, fsModifiers, vk);
}

bool MafiaBar::Hotkey::UnregisterHotKey(const HWND& handle, int hotkey_id) { return ::UnregisterHotKey(handle, hotkey_id); }

bool MafiaBar::WindowRegistery::RegistryWrite(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value)
{
    HKEY key;
    if (RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &key) == ERROR_SUCCESS)
    {
        if (RegSetValueEx(key, name, 0, type, (LPBYTE)value, strlen(value) * sizeof(char)) == ERROR_SUCCESS)
        {
            RegCloseKey(key);
            return true;
        }
        else { return false; }
    }
    else { return false; }
}

char* MafiaBar::WindowRegistery::RegistryRead(LPCTSTR subkey, LPCTSTR name, DWORD type)
{
    HKEY key;
    TCHAR value[255];
    DWORD value_length = 255;
    RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &key);
    RegQueryValueEx(key, name, NULL, &type, (LPBYTE)&value, &value_length);
    RegCloseKey(key);
    static char converted[MAX_NAME_STRING];
    wcstombs(converted, value, wcslen(value) + 1);
    return std::move(converted);
}

MafiaBar::Time::Time(const char* Process_Describ)
    : start(std::chrono::high_resolution_clock::now()), label(Process_Describ)  
{ 
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

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

MafiaBar::Console::Console(const char* cmdcolor)
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout); // output only

    freopen_s(&fp, "CONIN$", "r", stdin); //input only

    SetConsoleTitleA(ConsoleTitle.c_str());

    system(cmdcolor);

    printf("\t\t\t\t\t\tWelcome to Mafia Bar Engine\n");
}

HWND MafiaBar::Console::GetConsoleHandle() const { return GetConsoleWindow(); }

std::string MafiaBar::Console::GetConsoleTitle() const { return ConsoleTitle; }

int MafiaBar::Console::GetColumnWidthConsole()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE out;

    if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
        !GetConsoleScreenBufferInfo(out, &info))
        return 80;
    return info.dwSize.X;
}
