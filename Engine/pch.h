#pragma once
/*
		-----------------pch.h------------------
			-----PreCompiled Header File-----
*/

//Implementing DirectX libraries
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

#include <dxgi.h>
#pragma comment(lib, "dxgi.lib")

//Implementing DirectXTK library
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"
#include "DirectXTK/ScreenGrab.h"
#include "DirectXTK/CommonStates.h"

#ifdef _DEBUG
	#pragma comment(lib, "../Engine/DirectXTK/Binary/DebugLibrary/DirectXTK.lib")
#else
	#pragma comment(lib, "../Engine/DirectXTK/Binary/ReleaseLibrary/DirectXTK.lib")
#endif

//Microsoft Windows Includes
#include <Windows.h>
#include <wrl.h>
#include <windowsx.h>
#include <wincodec.h>

//STD Includes
#include <chrono>
#include <thread>
#include <fstream>
#include <random>
#include <mutex>
#include <future>
#include <filesystem>

//MafiaBar SDK Includes
#include <Vector.h>
#include <VirtualVector.h>

typedef BSTR CS_String;
typedef std::string CP_String;
typedef const char* C_String;
typedef HRESULT DebugCode;

