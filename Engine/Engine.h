#pragma once
#pragma warning(push)
#pragma warning(disable: 4577)
#pragma warning(disable:26444)
#pragma warning(disable:26495)

#define __FUNCTION_SIGNATURE__ __FUNCSIG__

#include "Definitions.h"

#include "pch.h"

#include "FileSystem.h"

#include "Keyboard.h"

#include "Mouse.h"

#include "Exception.h"

#include "Logger.h"

#include "GraphicDataTypes.h"

#include "Graphics.h"

/// <summary>Mafia Bar Engine Utilities aren't meant to be apart of Engine.h.
/// <para>But if you want to include them into your Engine.h define ENGINE_UTILS definition before including Engine.h in your program.</para>
/// </summary>
#ifdef ENGINE_UTILS

#include "Console"

#include "DependencyFiles.h"

#include "Information.h"

#include "FPSCounter.h"

#include "MB_Utils.h"

#endif //ENGINE_UTILS

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Engine final
		{			
			static std::mutex mutex;
			Engine() = default;
			~Engine();
		public:
			Engine(Engine& other) = delete;
			void operator=(const Engine&) = delete;
			void CreateGraphics(HWND hwnd, bool Fullscreen, bool Vsync, int Width = 0, int Height = 0);
		public:
			static Engine& Get();
			constexpr MafiaBar::Keyboard& GetKeyboard();
			constexpr MafiaBar::Mouse& GetMouse();
			constexpr MafiaBar::Engine::Logger& GetLogger();
			constexpr MafiaBar::Engine::Exception& GetException();
			constexpr MafiaBar::Engine::Graphics::Graphics* GetGraphics();
		private:
			MafiaBar::Keyboard Keyboard;
			MafiaBar::Mouse Mouse;
			MafiaBar::Engine::Logger Log;
			MafiaBar::Engine::Exception Exception;
			MafiaBar::Engine::Graphics::Graphics* Graphics;
		};
	}
}

namespace MafiaBar
{
	namespace Engine
	{	
		//Tries the function if it throws an exception or not with try,catch statements and if it throws shows a Ignore,Retry,Abort message box with the description. 
		//Note: For now this function doesn't support class function pointers
		//Example: void Foo(int a ) { printf_s("%d", a); }
		//	 tryex(Foo, __FILE__, __FUNCSIG__, __LINE__, 2);
		template<typename C, typename... Argv>
		void tryex(C&& function, const char* File, const char* Function, int Line, Argv... args)
		{
			try { (*function)(std::forward<Argv>(args)...); }
			catch (const std::exception& e)
			{
				MafiaBar::Engine::Logger::MessageEx(
					"Mafia Bar Engine tryex",
					MB_ABORTRETRYIGNORE | MB_ICONERROR,
					FindWindowA(NULL, "Mafia Bar Engine"),
					"Try Failed!\n[Exception Description]  %s\n[File] %s\n[Function] %s\n[Line] %d\n", e.what(), File, Function, Line);
			}
		}
		//Release the COM objects safely
		inline void SafeRelease(IUnknown** value)
		{
			if (*value)
			{
				(*value)->Release();
				*value = 0;
			}
		}
	}
}

#pragma warning(pop)
