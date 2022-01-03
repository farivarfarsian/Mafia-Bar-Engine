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

void MafiaBar::Console::CreateWIN32Console()
{
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout); // output only

    freopen_s(&fp, "CONIN$", "r", stdin); //input only

    SetConsoleTitleA("Mafia Bar Engine: Debug Console");
}

void MafiaBar::Console::CreateConsole(HWND ParentWindowHandle)
{
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
