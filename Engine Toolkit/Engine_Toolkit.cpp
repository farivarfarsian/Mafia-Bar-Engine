#include "Engine_Toolkit.h"

EXP_ENGINE_F char* Engine::registry_read(LPCTSTR subkey, LPCTSTR name, DWORD type)
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
EXP_ENGINE_F void Engine::registry_write(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value)
{
    HKEY key;
    RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &key);
    RegSetValueEx(key, name, 0, type, (LPBYTE)value, strlen(value) * sizeof(char));
    RegCloseKey(key);
}

BOOL Engine::Hotkey::RegisterHotKey(const HWND& handle, int& hotkey_id, const int& fsModifiers, const int& vk)
{
    return ::RegisterHotKey(handle, hotkey_id, fsModifiers, vk);
}

BOOL Engine::Hotkey::UnregisterHotKey(const HWND& handle, int& hotkey_id)
{
    return ::UnregisterHotKey(handle, hotkey_id);
}