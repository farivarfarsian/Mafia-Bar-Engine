#ifndef MB_ENGINE
#define MB_ENGINE

#pragma once
#pragma warning(push)
#pragma warning(disable: 4577)
#pragma warning(disable:26444)
#pragma warning(disable:26495)

#include "def.h"

#include "pch.h"

#include "FileSystem.h"

#include "Keyboard.h"

#include "Mouse.h"

#include "Exception.h"

#include "Logger.h"

#include "Application.h"

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
			Engine(Engine& Engine) = delete;
			Engine& operator=(const Engine&) = delete;
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

#pragma warning(pop)

#endif //MB_ENGINE