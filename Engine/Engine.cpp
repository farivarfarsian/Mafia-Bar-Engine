#include "Engine.h"

std::mutex MafiaBar::Engine::Engine::mutex;

MafiaBar::Engine::Engine& MafiaBar::Engine::Engine::Get()
{
    std::lock_guard<std::mutex> lock(mutex);
    static Engine Engine;   
    return Engine;
}

void MafiaBar::Engine::Engine::CreateGraphicsAndScene(HWND hwnd, bool Fullscreen, bool Vsync, int Width, int Height)
{ 
    Graphics.Initialize(hwnd, Fullscreen, Vsync, Width, Height);  
    Scene.Initialize(&Graphics);
}

void MafiaBar::Engine::Engine::Shutdown()
{
    MafiaBar::Engine::Engine::Get().GetKeyboard().~Keyboard();
    MafiaBar::Engine::Engine::Get().GetMouse().~Mouse();
    MafiaBar::Engine::Engine::Get().GetException().~Exception();
    MafiaBar::Engine::Engine::Get().GetLogger().~Logger();
    MafiaBar::Engine::Engine::Get().GetScene().~Scene();
    MafiaBar::Engine::Engine::Get().GetUI().~UI();
    MafiaBar::Engine::Engine::Get().GetGraphics().~Graphics();
}

constexpr MafiaBar::Keyboard& MafiaBar::Engine::Engine::GetKeyboard() { return Keyboard; }

constexpr MafiaBar::Mouse& MafiaBar::Engine::Engine::GetMouse() { return Mouse; }

constexpr MafiaBar::Engine::Logger& MafiaBar::Engine::Engine::GetLogger() { return Log; }

constexpr MafiaBar::Engine::Graphics::Graphics& MafiaBar::Engine::Engine::GetGraphics() { return Graphics; }

constexpr MafiaBar::Engine::Scene& MafiaBar::Engine::Engine::GetScene() { return Scene; }

constexpr MafiaBar::Engine::UI& MafiaBar::Engine::Engine::GetUI() { return UI; }

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

