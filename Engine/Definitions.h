#pragma once

#define MAX_NAME_STRING 512

#define FETAL_ERROR(DESC) MafiaBar::Engine::Logger::FetalError(DESC, __FILE__, __FUNCSIG__, __LINE__)
#define ERROR_MESSAGE(TITLE, MESSAGE) MafiaBar::Engine::Logger::Message(TITLE, MESSAGE, MB_ICONERROR) 

#define MB_EXCEPTION(DEBUG_CODE) MafiaBar::Engine::Exception(__FILE__, __FUNCSIG__, __LINE__, DEBUG_CODE)

#define LINK_LIBRARY(LIB_NAME) __pragma(comment(lib, LIB_NAME))

#ifdef MB_ENGNE
	#ifdef MB_ENGINE_LIBRARY
		#define MB_ENGINE_API __declspec(dllexport)
	#else
		#define MB_ENGINE_API __declspec(dllimport)
	#endif 
#endif //MB_ENGINE

#define MB_ENGINE_API_FUNCTION extern "C" __declspec(dllexport)