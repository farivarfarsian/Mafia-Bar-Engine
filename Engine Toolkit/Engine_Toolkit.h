#pragma once
#define size_of(object) (char *)(&object+1) - (char *)(&object)
#define CLEAR_CONSOLE system("cls")

#include "../Mafia Bar Engine/pch.h"

namespace Engine
{
    EXP_ENGINE_F char* registry_read(LPCTSTR subkey, LPCTSTR name, DWORD type);
    EXP_ENGINE_F void registry_write(LPCTSTR subkey, LPCTSTR name, DWORD type, const char* value);
    struct EXP_ENGINE Hotkey
    {
        int hotkey_id = 0;
        static BOOL RegisterHotKey(const HWND& handle, int& hotkey_id, const int& fsModifiers, const int& vk);
        static BOOL UnregisterHotKey(const HWND& handle, int& hotkey_id);
    };
    struct Console
    {
        static void CreateConsole(const char* cmdcolor = 0)
        {
            AllocConsole();
            FILE* fp;
            freopen_s(&fp, "CONOUT$", "w", stdout); // output only

            freopen_s(&fp, "CONIN$", "r", stdin); //input only

            SetConsoleTitleA("Mafia Bar Engine: Debug Console");

            system(cmdcolor);
        }
        static void WelcomeMessage(const char* username)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
            printf("\t\t\t\t\tWelcome to Mafia Bar Engine %s\n", username);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        static int GetColumnWidthConsole()
        {
            CONSOLE_SCREEN_BUFFER_INFO info;
            HANDLE out;

            if (!(out = GetStdHandle(STD_OUTPUT_HANDLE)) ||
                !GetConsoleScreenBufferInfo(out, &info))
                return 80;
            return info.dwSize.X;
        }
    #ifdef CONSOLE_GUI
        static void PrintfCenetredText(const char* Text)
        {
            const int field_width = (GetColumnWidthConsole() - strlen(Text)) / 2 + strlen(Text);
            printf("%*s", field_width, Text);
        }
        static void PritnfColoredText(const char* Text, WORD color)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            printf_s("%s", Text);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        static void PritnfCenteredColoredText(const char* Text, WORD color)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            const int field_width = (GetColumnWidthConsole() - strlen(Text)) / 2 + strlen(Text);
            printf_s("%*s", field_width, Text);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    #endif // CONSOLE_GUI
    };
#ifdef _CRT_SECURE_NO_WARNINGS_DEBUG
//Only For Debugging
    struct Timer
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::duration<double> duration;
        const char* label;
    public:
        Timer(const char* Process_Describ)
            : start(std::chrono::high_resolution_clock::now()), label(Process_Describ)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf_s("Timer Started\t%s\n", Process_Describ);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        void End()
        {
            end = std::chrono::high_resolution_clock::now();
            duration = end - start;

            float ms = duration.count() * 1000.0f;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
            printf("The Procces: %s Took: %fms\n", label, ms);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        }
    };
#else
#define NO_DEBUG
#endif // _CRT_SECURE_NO_WARNINGS_DEBUG
}
