#pragma once
#include "def.h"
#include "pch.h"


namespace MafiaBar
{
    namespace Engine
    {
        namespace Utilities
        {

            /*---------------Window Registery Read/Write Class---------------*/
            class MB_ENGINE_API WinRegistery
            {
            public:
                //Write a window registery, if the return value is true the opperation have completed.
                bool RegistryWrite(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value);
                //Read a registery, the return is a string.
                char* RegistryRead(LPCTSTR subkey, LPCTSTR name, DWORD type);
            };
        }
    }
}



