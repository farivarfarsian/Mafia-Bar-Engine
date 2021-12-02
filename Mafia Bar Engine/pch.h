#pragma once
/*
* 
*PreCompiled Header File
* 
*/

#ifdef _CRT_SECURE_NO_WARNINGS_DEBUG
//Only For Debugging
#include <iostream>
#include <chrono>
#endif // _CRT_SECURE_NO_WARNINGS_DEBUG


// DirectX includes
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXColors.h>


#include <windowsx.h> //Windows Mouse Events


#include <thread> //Thread


#include "resource.h" //Resources


#include <fstream> //Logger

#include <queue>// Std::queue For Storing Windows Events Like KeyBoard And Mouse

#include <optional>


//Definitions
#define MAX_NAME_STRING 256
#define IsDown 0x8000


#define EXP_ENGINE __declspec(dllexport)
#define EXP_ENGINE_F extern "C" __declspec(dllexport)
#define IMP_ENGINE __declspec(dllimport)

#define MB_EXCEPTION( hr ) Window::GENGW_Exceptions(__LINE__, __FILE__, hr);
#define MB_LAST_EXCEPTION 	Window::GENGW_Exceptions(__LINE__, __FILE__, GetLastError());

//DirectX Lib Files
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")


#pragma comment(lib,"DirectXTK.lib") //DirectXTK Lib File



