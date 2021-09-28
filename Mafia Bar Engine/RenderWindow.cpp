#include "pch.h"
#include "RenderWindow.h"
LRESULT WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	RenderWindow rw;
	switch (message)
	{
	case WM_KEYDOWN:
		rw.keyboard.OnKeyPressed(static_cast<unsigned char>(wparam));
		printf_s("KeyPressed\n");
		break;
	case WM_KEYUP:
		rw.keyboard.OnKeyReleased(static_cast<unsigned char>(wparam));
		printf_s("KeyReleased\n");
		break;
	case WM_CHAR:
		rw.keyboard.OnChar(static_cast<char>(wparam));
		printf_s("KeyChar\n");
		break;

	case WM_LBUTTONDOWN:
		printf("%d, %d\n", GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}

bool RenderWindow::Initialize(HINSTANCE hInstance, int width, int height)
{

    this->hInstance = hInstance;


    this->RegisterWindowClass();

	this->handle = CreateWindowEx(WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT,
			this->WindowClass, //Window Class name
			this->WindowTitle, //Windows Title
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows Styles
			CW_USEDEFAULT, //Window X Position
			CW_USEDEFAULT, //Windows Y Posiontion
			width, //Window Width
			height, //Window Height
			nullptr, //Handle of Parent of this Windows
			nullptr, //Handle to menu or Child Windows Identifier
			hInstance, //handle to the instance of module to be used with this class
			this); //Param to Create Window
	
	if (this->handle == NULL)
	{

		return false;
	}
	//Showing Window
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

    return true;
}

bool RenderWindow::ProcessMessages()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
	}

	return true;
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL)
	{
		UnregisterClass(this->WindowClass, this->hInstance);
		DestroyWindow(handle);
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wcex.hIcon = static_cast<HICON>(LoadImage( hInstance, MAKEINTRESOURCE( IDI_ICON1 ), IMAGE_ICON, 32 ,32 , 0));
	wcex.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE( IDI_ICON1 ), IMAGE_ICON, 16, 16, 0));;

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = hInstance;

	wcex.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcex);
}

RenderWindow::GENGW_Exceptions::GENGW_Exceptions(int line, const char* file, HRESULT hr) noexcept
	: Exceptions(line, file), hr( hr )
{
	printf_s("[Mafia Bar Engine Exception System]\tAn Exception Threw\n");
}

const char* RenderWindow::GENGW_Exceptions::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << '\n' << " [Error Code] " << hr << '\n'
		<< " [Describtion] " << GetErrorString()  << GetOriginString();
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* RenderWindow::GENGW_Exceptions::GetType() const noexcept
{
	return "Mafia Bar Engine Exception";
}

std::string RenderWindow::GENGW_Exceptions::TranslteErrorCodes(HRESULT hr) noexcept
{
	char* msgbuffer = nullptr;
	DWORD nmsglen = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS
		, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&msgbuffer), 0 , nullptr);

	if (nmsglen == 0)
	{
		return "Unidentified Error Code";
	}
	std::string errorstring = msgbuffer;
	LocalFree(msgbuffer);
	return errorstring;
}

std::string RenderWindow::GENGW_Exceptions::GetErrorString() const noexcept
{
	return TranslteErrorCodes(hr);
}
