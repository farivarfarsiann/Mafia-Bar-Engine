#include "WinRegistery.h"

bool MafiaBar::Engine::Utilities::WinRegistery::RegistryWrite(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value)
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

char* MafiaBar::Engine::Utilities::WinRegistery::RegistryRead(LPCTSTR subkey, LPCTSTR name, DWORD type)
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
