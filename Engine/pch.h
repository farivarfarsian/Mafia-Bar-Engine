#pragma once
/*
		-----------------pch.h------------------
			-----PreCompiled Header File-----
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
#include <random>
#include <yvals.h>

//MafiaBar SDK Includes
#include <Vector.h>


typedef HRESULT DebugCode;





