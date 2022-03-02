#include "Engine.h"

std::mutex MafiaBar::Engine::Engine::mutex;

MafiaBar::Engine::Engine::~Engine() { delete Graphics; }

MafiaBar::Engine::Engine& MafiaBar::Engine::Engine::Get()
{
    std::lock_guard<std::mutex> lock(mutex);
    static Engine Engine;
    return Engine;
}

void MafiaBar::Engine::Engine::CreateGraphics(HWND hwnd, bool Fullscreen, bool Vsync, int Width, int Height)  { Graphics = new MafiaBar::Engine::Graphics::Graphics(hwnd, Width, Height, Fullscreen, Vsync);  }

constexpr MafiaBar::Keyboard& MafiaBar::Engine::Engine::GetKeyboard() { return Keyboard; }

constexpr MafiaBar::Mouse& MafiaBar::Engine::Engine::GetMouse() { return Mouse; }

constexpr MafiaBar::Engine::Logger& MafiaBar::Engine::Engine::GetLogger() { return Log; }

constexpr MafiaBar::Engine::Graphics::Graphics* MafiaBar::Engine::Engine::GetGraphics() { return Graphics; }

constexpr MafiaBar::Engine::Exception& MafiaBar::Engine::Engine::GetException() { return Exception; }

int __stdcall DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            break;
        case DLL_PROCESS_DETACH:
            Sleep(100);
            FreeLibraryAndExitThread(hinstDLL, 0);
            break;
    }
    return TRUE; 
}

