#pragma once
#include "Definitions.h"
#include "pch.h"

namespace MafiaBar
{
	namespace Engine
	{
		/// <summary>
		/// Mafia Bar Engine Exception class is a class which handles HRESULT codes that win-api and DirectX 11 functions return. 
		/// <para>This class Formats the HRESULT codes by FormatMessageA() and show a Ignore,Rety,Abort message box.</para>
		/// <para>For checking the DebugCodes use "Check" function like this:</para>
		/// <para>Example:</para>
		///	<para>Exception exception;</para>
		///	exception.Check(__FILE__, __FUNCSIG__, __LINE__, E_FAIL);
		/// <para>Note: Don't use this class with try,catch statements for them use std::exception</para>
		/// </summary>
		class MB_ENGINE_API Exception
		{
		public:
			Exception() noexcept = default;
			virtual ~Exception() noexcept;
			Exception(const char* File, const char* Function, int Line, DebugCode DebugCode) noexcept;
			void Check(const char* File, const char* Function, int Line, DebugCode DebugCode) noexcept;
			const char* what() const noexcept;
			virtual const char* GetType() const noexcept { return "Mafia Bar Engine Exception"; }
		protected:		
			DebugCode DC = S_OK;
			LPSTR Description = NULL;
			std::stringstream StringStream;
			void Throw(const char* Subject);
		};
		class MB_ENGINE_API GraphicException final : public Exception
		{
			GraphicException() = default;
			~GraphicException() = default;
			GraphicException(const char* File, const char* Function, int Line, DebugCode DebugCode) noexcept;
			const char* GetType() const noexcept override;
		};
	}
}


