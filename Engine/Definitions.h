#pragma once

#define MAX_NAME_STRING 512

#define EXP_ENGINE __declspec(dllexport)
#define EXP_ENGINE_F extern "C" __declspec(dllexport)
#define IMP_ENGINE __declspec(dllimport)

#define MB_EXCEPTION( hr ) Window::GENGW_Exceptions(__LINE__, __FILE__, hr);
#define MB_LAST_EXCEPTION 	Window::GENGW_Exceptions(__LINE__, __FILE__, GetLastError());

#define FETAL_ERROR(DESC) MafiaBar::Engine::Logger::FetalError(DESC, __FILE__, __FUNCSIG__, __LINE__)
#define ERROR_MESSAGE(TITLE, MESSAGE) MafiaBar::Engine::Logger::Message(TITLE, MESSAGE, MB_ICONERROR) 

#define MB_GRAPHIC_EXCEPTION(DEBUG_CODE) MafiaBar::Engine::Graphics::GraphicException(__FILE__, __FUNCSIG__, __LINE__, DEBUG_CODE)

#define LINK_LIBRARY(LIB_NAME) __pragma(comment(lib, LIB_NAME))
