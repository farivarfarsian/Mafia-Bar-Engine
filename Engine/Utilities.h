#pragma once
#include "def.h"
#include "pch.h"
#include "Logger.h"
#include "Exception.h"

namespace MafiaBar
{
	namespace Utilities
	{
		class MB_ENGINE_API Time
		{
		public:
			Time(const char* Process_Describ);
			Time();
			void Start(const char* Process_Describ);
			void End();
		public:
			float Mark();
			float Peek() const;
			const char* GetCurrentDateAndTime();
		private:
			std::chrono::time_point<std::chrono::steady_clock> start, end;
			std::chrono::duration<double> duration;
			const char* label;
			std::chrono::steady_clock::time_point last;
		};

		MB_ENGINE_API constexpr const DWORD GetProcessID(HWND Handle = NULL);

		MB_ENGINE_API char* GetProgramFullPath(HINSTANCE hInstance);

		MB_ENGINE_API void SetWindowTransparency(HWND Handle, uint8_t Transperancy);

		MB_ENGINE_API void SetWindowAsOverlay(HWND Handle);

		MB_ENGINE_API BOOL CenterWindow(HWND Handle, int Width = 0, int Height = 0);

		MB_ENGINE_API bool IsWindows11OrGreater();

		MB_ENGINE_API void TakeScreenshot(IDXGISwapChain* SwapChain, ID3D11DeviceContext* DeviceContext, HWND WindowHandle = NULL);

		enum WindowTransparency
		{
			Nothing = 0x00,
			Half = 0xFF / 2,
			Full = 0xFF
		};

		/// <summary>
		/// Tries the function if it throws an exception or not with try,catch statements and if it throws shows a Ignore,Retry,Abort message box with the description.
		/// Remember to specify the return value of the function pointer or lambda correctly.
		/// </summary>
		/// <typeparam name="Return">Specify the return value of the function</typeparam>
		/// <typeparam name="C"></typeparam>
		/// <typeparam name="...Argv"></typeparam>
		/// <param name="const char* File ">Use __FILE__</param>
		/// <param name="const char* FunctionNameCalled ">Use __FUNCSIG__</param>
		/// <param name="int Line ">Use __LINE__</param>
		/// <param name="Function ">Pass your function pointer or lambda</param>
		/// <param name="Argv... args">Pass the parameters that your function needs</param>
		/// <returns>It will return the value that the function pointer or lambda has returned</returns>
		template<typename Return, typename C, typename... Argv>
		Return tryex(const char* File, const char* FunctionNameCalled, int Line, C&& Function, Argv... args)
		{
			try
			{
				return (Function)(std::forward<Argv>(args)...);
			}
			catch (const std::exception& e)
			{
			#ifdef _WIN32
				MafiaBar::Engine::Logger::MessageEx(
					"Mafia Bar Engine",
					MB_ABORTRETRYIGNORE | MB_ICONERROR,
					FindWindowA(NULL, "Mafia Bar Engine"),
					"Try Failed!\n[Exception Description]  %s\n[File] %s\n[Function] %s\n[Line] %d\n", e.what(), File, FunctionNameCalled, Line);
			#else
				throw std::exception(e.what());
			#endif
			}
		}

		/// <summary>
		/// 
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="FullName[Optional] ">Specify if you want the full name of the data type that you have passed in or just the name of it</param>
		/// <returns>The type of the data type that you have passed into the template as c_string</returns>
		template<typename T>
		const char* GetTypeName(bool FullName = false)
		{
			static std::string Name = typeid(T).name();

			if (FullName == true) { return Name.c_str(); }

			int Index = Name.find("class ");
			if (Index != std::string::npos)
			{
				static std::string Buffer;
				for (int i = 6; i < Name.length(); i++)
				{
					Buffer += Name[i];
				}
				return Buffer.c_str();
			}
			else
			{
				static std::string Buffer;
				for (int i = 7; i < Name.length(); i++)
				{
					Buffer += Name[i];
				}
				return Buffer.c_str();
			}
		}
	}
}

//Utilities Definitions:

#define try(ReturnType, ...) MafiaBar::Utilities::tryex<ReturnType>(__FILE__, __FUNCTION_SIGNATURE__, __LINE__ , __VA_ARGS__);
