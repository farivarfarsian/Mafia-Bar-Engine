#pragma once
/*
* 
*	PreCompiled Header File
* 
*/

//Implementing DirectX Libraries
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include <d3d9.h> 
#pragma comment(lib, "d3d9.lib")

#include <d3dcompiler.h>
#pragma comment(lib, "D3DCompiler.lib")

#include <d3dx11.h>
#pragma comment(lib, "d3dx11.lib")

#include <DirectXMath.h>
#include <DirectXColors.h>

//Microsoft Windows Includes
#include <Windows.h>
#include <wrl.h>
#include <windowsx.h>

//STD Includes
#include <chrono>
#include <thread>
#include <fstream>
#include <queue>
#include <bitset>


//MafiaBar SDK Includes
#include <Vector.h>

#define MAX_NAME_STRING 256

#define EXP_ENGINE __declspec(dllexport)
#define EXP_ENGINE_F extern "C" __declspec(dllexport)
#define IMP_ENGINE __declspec(dllimport)

#define MB_EXCEPTION( hr ) Window::GENGW_Exceptions(__LINE__, __FILE__, hr);
#define MB_LAST_EXCEPTION 	Window::GENGW_Exceptions(__LINE__, __FILE__, GetLastError());



