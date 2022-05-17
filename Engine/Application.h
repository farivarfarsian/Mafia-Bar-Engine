#pragma once
#include "Engine.h"

//Using MafiaBar::Utilities::IsWindows11OrGreater() 
#include "Utilities.h"

//Customising the Window with DWM API (Windows Only)
#ifdef _WIN32
#include <dwmapi.h>
LINK_LIBRARY("Dwmapi.lib")
#endif

namespace MafiaBar
{
	namespace Engine
	{
		class MB_ENGINE_API Application
		{
		public:
			Application() = default;
			Application(const Application&) = delete;
			Application& operator=(const Application&) = delete;
			virtual ~Application();
			int Present();
			void Initialize(const char* Title, const char* ClassName, int Width, int Height, bool Fullscreen = false, int IconResourceFileID = 32512, int CursorResourceFileID = 32512);
			void Restart();
			void Exit(int ExitCode);
		public:
			constexpr HWND GetHandle() const;
			constexpr DWORD GetID() const;
			constexpr HINSTANCE GetInstance() const;
			constexpr int GetWidth() const;
			constexpr int GetHeight() const;
			constexpr const char* GetTitle() const;
			constexpr bool GetFullScreen() const;
			constexpr bool GetFocus() const;
		public:
			static enum ApplicationErrorCodes
			{
				SUCCEEDED = 0,
				TRYING_TO_RUN_MULTIPLE_INSTANCES_OF_APPLICATION = 6456
			};
		private:
			std::optional<int> ProcessMessages();
			static LRESULT __stdcall WindowProcedureSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			static LRESULT __stdcall WindowProcedureThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			LRESULT WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		protected:
			//This function runs when Application received WM_CREATE message.
			virtual void OnCreate();
			//This function runs when Application received WM_CLOSE message.
			virtual void OnClose();
			//This function runs before initializing the Application.
			virtual void BeforeInitialize();
			//This function runs after initializing the Application.
			virtual void AfterInitialize();
			//This function runs when Application received WM_SETFOCUS message.
			virtual void OnFocus();
			//This function runs on Present method before the program loop.
			virtual void Setup();
			//Do your rendering operations here.
			virtual void Frame();
			DWORD ApplicationID = GetCurrentProcessId();
			HWND ApplicationHandle = NULL;
			HINSTANCE ApplicationInstance = GetModuleHandleA(NULL);
			const char* ApplicationTitle = nullptr;
			const char* ApplicationClassName = nullptr;
			int Width = 0, Height = 0;
			bool IsFullScreen = false, IsFocus = false, OneApplicationGuard = false;
		};
	}
}

