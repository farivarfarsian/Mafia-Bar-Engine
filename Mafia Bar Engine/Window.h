#pragma once
#include "pch.h"
#include <MB_Graphics.h>
#include <MB_Exception.h>
#include <MB_Keyboard.h>
#include <MB_Mouse.h>
#include <MB_Utils.h>

class Window
{
public:
	MafiaBar::Keyboard keyboard;
	MafiaBar::Mouse mouse;
	MafiaBar::Console console;
	MafiaBar::Hotkey hotkey;
	MafiaBar::Logger log;
	MafiaBar::WindowDialogs windialogs;
	std::unique_ptr<MafiaBar::Graphics> graphics;
public:
	struct GENGW_Exceptions : public MafiaBar::Exceptions
	{
		GENGW_Exceptions(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TranslteErrorCodes(HRESULT hr) noexcept;
		std::string GetErrorString() const noexcept;
		HRESULT hr;
	};
public:
	Window() = default;
	Window(const char* WinTitle, int width, int height, bool fullscreen);
	std::optional<int> ProcessMessages();
	static LRESULT __stdcall WindowProcedureSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT __stdcall WindowProcedureThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void RegisterWindowClass();
	~Window();
public:
	enum Transparency
	{
		Nothing = 0x00,
		Half = 0xFF / 2,
		Full = 0xFF
	};
	void SetWindowTransparency(std::uint8_t Transperancy);
	void SetWindowAsOverlay();
	void AddMenus(HWND hwnd);
	BOOL CenterWindow(HWND hwndWindow);
	void ScreenShot(HWND hwnd, const char* BmpName)
	{
		/*
		if (BmpName != "\0")
		{
			HDC WindowDC = GetDC(hwnd);

			DWORD FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * (Width * Height * 4));
			char* BmpFileData = (char*)GlobalAlloc(0x0040, FileSize);

			PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
			PBITMAPINFOHEADER  BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];

			BFileHeader->bfType = 0x4D42; // BM
			BFileHeader->bfSize = sizeof(BITMAPFILEHEADER);
			BFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

			BInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
			BInfoHeader->biPlanes = 1;
			BInfoHeader->biBitCount = 24;
			BInfoHeader->biCompression = BI_RGB;
			BInfoHeader->biHeight = Height;
			BInfoHeader->biWidth = Width;

			RGBTRIPLE* Image = (RGBTRIPLE*)&BmpFileData[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];
			RGBTRIPLE color;

			HDC CaptureDC = CreateCompatibleDC(WindowDC);
			Sleep(2000);
			HBITMAP CaptureBitmap = CreateCompatibleBitmap(WindowDC, Width, Height);
			SelectObject(CaptureDC, CaptureBitmap);
			BitBlt(CaptureDC, 0, 0, Width, Height, WindowDC, 0, 0, SRCCOPY | CAPTUREBLT);
			GetDIBits(CaptureDC, CaptureBitmap, 0, Height, Image, (LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

			DWORD Junk;
			HANDLE FH = CreateFileA(BmpName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
			WriteFile(FH, BmpFileData, FileSize, &Junk, 0);
			CloseHandle(FH);
			GlobalFree(BmpFileData);
		}
		*/
	}
	/*
	HRESULT blTakeScreenShot()
	{
		IDirect3D9* p_d3d;  //Presumed to be properly initialized already


		D3DFORMAT format = D3DFMT_R5G6B5; //For simplicity we'll hard-code this for now.

		D3DPRESENT_PARAMETERS pp;
		IDirect3DDevice9* p_device = NULL;
		HRESULT hr;

		//Even though we set all of it's members, it's still good practice to zero it out

		ZeroMemory(&pp, sizeof(D3DPRESENT_PARAMETERS));

		pp.BackBufferCount = 1;  //We only need a single back buffer

		pp.MultiSampleType = D3DMULTISAMPLE_NONE; //No multi-sampling

		pp.MultiSampleQuality = 0;                //No multi-sampling

		pp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // Throw away previous frames, we don't need them

		pp.hDeviceWindow = handle;  //This is our main (and only) window

		pp.Flags = 0;            //No flags to set

		pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //Default Refresh Rate

		pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;   //Default Presentation rate

		pp.BackBufferFormat = format;      //Display format

		pp.EnableAutoDepthStencil = FALSE; //No depth/stencil buffer


		if (fullscreen) {
			pp.Windowed = FALSE;
			pp.BackBufferWidth = 640;
			pp.BackBufferHeight = 480;
		}
		else {
			pp.Windowed = TRUE;
		}

		hr = p_d3d->CreateDevice(D3DADAPTER_DEFAULT, //The default adapter, on a multi-monitor system

												   //there can be more than one.

			D3DDEVTYPE_HAL, //Use hardware acceleration rather than the software renderer

			//Our Window

			handle,
			//Process vertices in software. This is slower than in hardware,

			//But will work on all graphics cards.

			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			//Our D3DPRESENT_PARAMETERS structure, so it knows what we want to build

			&pp,
			//This will be set to point to the new device

			&p_device);
		if (FAILED(hr)) {
			// Handle error

		}

		LPDIRECT3DSURFACE9 frontbuf;
		char filename[64];
		FILE* f;
		int x, y;
		RECT rcWindow;
		// look for the next free file
		for (int i = 0; i < 999; i++)
		{
			// build the filename
			sprintf(filename, "screen%.3d.bmp", i);
			f = fopen(filename, "r");
			if (f == NULL)
				break;
			else
				fclose(f);
		}

		// get the screen resolution. If it's a windowed application get the whole
		// screen size. If it's a fullscreen application you might have somewhere
		// your defines as: #define SCREEN_WIDTH 800
		if (fullscreen)
		{
			x = Width;
			y = Height;
		}
		else
		{
			x = GetSystemMetrics(SM_CXSCREEN);
			y = GetSystemMetrics(SM_CYSCREEN);
			// to get the window sizes
			GetWindowRect(handle, &rcWindow);
		}
		// here we create an empty Surface. The parameter D3DFMT_A8R8G8B8 creates an 32 bit image with
		// an alpha channel and 8 bits per channel.
		if (FAILED(hr = p_device->CreateOffscreenPlainSurface(x, y, D3DFMT_A8R8G8B8, D3DPOOL_SCRATCH, &frontbuf, NULL)))
			return hr;
		// now we copy the entire frontbuffer into our new surface. The first parameter is NULL since
		// we assume we have only one swap chain
		if (FAILED(hr = p_device->GetFrontBufferData(NULL, frontbuf)))
		{
			// if this fails release our surface so we have no memory leak
			frontbuf->Release();
			return hr;
		}
		// This is the most important functions. The DirectX-SDK provides this handy little function to
		// save our surface to a file. The first parameter is our specified filename, the second parameter
		// tells DirectX what kind of file we want to save (in this example we decide to save to BMP)
		// Note the difference between a fullscreen screenshot and a windowed one. If we have a windowed application
		// we only want the specified RECT saved from our screen capture
		if (fullscreen)
			D3DXSaveSurfaceToFileA(filename, D3DXIFF_BMP, frontbuf, NULL, NULL);
		else
			D3DXSaveSurfaceToFileA(filename, D3DXIFF_BMP, frontbuf, NULL, &rcWindow);
		frontbuf->Release();
		return hr;
	}
	*/
public:
	HWND GetHandle() const { return handle; }
	HINSTANCE GetInstance() const { return hInstance; }
	DWORD GetProcessID() const { return ProcID; }
	int GetWindowWidth() const { return Width; }
	int GetWindowHeight() const { return Height; }
	bool GetFullscreenBoolean() const { return fullscreen; }
private:
	HWND handle = NULL;
	DWORD ProcID = GetCurrentProcessId();
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	int Width, Height;
	bool fullscreen;
	HMENU WindowMenus;
};