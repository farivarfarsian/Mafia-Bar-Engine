#include "pch.h"
#include "Window.h"
#include "resource.h"
/*--------------------------------------WNDPROC For Mafia Bar Engine--------------------------------------*/
LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	Window rw;
	switch (message)
	{
		/*------------------------------ Console Window Events ------------------------------*/
	case WM_CTLCOLORSTATIC:
	{
		HDC hdc = (HDC)wparam;
		SetBkMode(hdc, TRANSPARENT);
		rw.console.SetTextColor(0, 0, 255);
		SetTextColor(hdc, RGB(std::get<0>(rw.console.GetColors()), std::get<1>(rw.console.GetColors()), std::get<2>(rw.console.GetColors())));
		return (LRESULT)GetStockObject(BLACK_BRUSH);
	}
		/*------------------------------ Keyboard Events ------------------------------*/
	case WM_KEYDOWN:
	{
		rw.keyboard.OnKeyPressed(static_cast<unsigned char>(wparam));
		printf_s("KeyPressed\n");
		break;
	}
	case WM_KEYUP:
	{
		rw.keyboard.OnKeyReleased(static_cast<unsigned char>(wparam));
		printf_s("KeyReleased\n");
		break;
	}
	case WM_CHAR:
	{
		rw.keyboard.OnChar(static_cast<char>(wparam));
		printf_s("KeyChar\n");
		break;
	}
		/*------------------------------ Mouse Events ------------------------------*/
	case WM_MOUSEMOVE:
	{
		#pragma message(__FILE__ "(" _CRT_STRINGIZE(__LINE__) ")"  ": warning: " "This Mouse Class Doesn't Work, Pls Fix")
		const POINTS pt = MAKEPOINTS(lparam); //Stroing The Mouse Moved Position
		rw.mouse.OnMouseMove(pt.x, pt.y);
		//printf_s("%d, %d\n", rw.mouse.GetPosX(), rw.mouse.GetPosY());
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lparam); //Stroing The Mouse Moved Position
		rw.mouse.OnLeftPressed(pt.x, pt.y);
		printf("%d, %d\n", GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lparam); //Stroing The Mouse Moved Position
		rw.mouse.OnLeftReleased(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lparam); //Stroing The Mouse Moved Position
		rw.mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lparam); //Stroing The Mouse Moved Position
		rw.mouse.OnRightReleased(pt.x, pt.y);
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lparam); //Stroing The Mouse Moved Position
		if (GET_WHEEL_DELTA_WPARAM(wparam) > 0) { rw.mouse.OnWheelUp(pt.x, pt.y); }
		else if (GET_WHEEL_DELTA_WPARAM(wparam < 0)) { rw.mouse.OnWheelDown(pt.x, pt.y); }
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wparam, lparam);
}
/*--------------------------------------Initializing The Mafia Bar Engine Window--------------------------------------*/
Window::Window(const char* WinTitle, int width, int height)
{
	this->RegisterWindowClass();

	this->handle = CreateWindowExA(WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT,
		"Mafia Bar", //Window Class name
		WinTitle, //Windows Title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows Styles
		CW_USEDEFAULT, //Window X Position
		CW_USEDEFAULT, //Windows Y Posiontion
		width, //Window Width
		height, //Window Height
		nullptr, //Handle of Parent of this Windows
		nullptr, //Handle to menu or Child Windows Identifier
		hInstance, //handle to the instance of module to be used with this class
		this); //Param to Create Window

	if (this->handle == NULL) { MB_LAST_EXCEPTION; }

	CenterWindow(this->handle);
	SetFocus(this->handle);
	ShowWindow(this->handle, SW_SHOW);

	console.CreateWIN32Console();

	graphics = std::make_unique<MafiaBar::Graphics>(handle);
}
/*--------------------------------------Creates The Window Class/Style--------------------------------------*/
void Window::RegisterWindowClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursorFromFileA("Assets/mafia_bar_cursor/normal-select.cur");

	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wcex.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wcex.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));;

	wcex.lpszClassName = L"Mafia Bar";

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = hInstance;

	wcex.lpfnWndProc = WindowProcess;

	RegisterClassEx(&wcex);
}
/*--------------------------------------Creates The Window Class/Style--------------------------------------*/
std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}
Window::~Window()
{
	if (this->handle != NULL)
	{
		UnregisterClass(L"Mafia Bar", this->hInstance);
		DestroyWindow(handle);
	}
}
/*--------------------------------------Mafia Bar Engine Exceptions--------------------------------------*/
Window::GENGW_Exceptions::GENGW_Exceptions(int line, const char* file, HRESULT hr) noexcept
	: MafiaBar::Exceptions(line, file), hr( hr )
{
	printf_s("[Mafia Bar Engine Exception System]\tAn Exception Threw\n");
}
const char* Window::GENGW_Exceptions::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << '\n' << " [Error Code] " << hr << '\n'
		<< " [Describtion] " << GetErrorString()  << GetOriginString();
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}
const char* Window::GENGW_Exceptions::GetType() const noexcept
{
	return "Mafia Bar Engine Exception";
}
std::string Window::GENGW_Exceptions::TranslteErrorCodes(HRESULT hr) noexcept
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
std::string Window::GENGW_Exceptions::GetErrorString() const noexcept
{
	return TranslteErrorCodes(hr);
}
void Window::SetWindowTransparency(std::uint8_t Transperancy)
{
	long wAttr = GetWindowLong(handle, GWL_EXSTYLE);
	SetWindowLong(handle, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
	SetLayeredWindowAttributes(handle, 0, Transperancy, 0x02);
}
void Window::SetWindowAsOverlay() { ::SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); }

BOOL Window::CenterWindow(HWND hwndWindow)
{
	HWND hwndParent;
	RECT rectWindow, rectParent;

	// make the window relative to its parent
	if ((hwndParent = GetParent(hwndWindow)) != NULL)
	{
		GetWindowRect(hwndWindow, &rectWindow);
		GetWindowRect(hwndParent, &rectParent);

		int nWidth = rectWindow.right - rectWindow.left;
		int nHeight = rectWindow.bottom - rectWindow.top;

		int nX = ((rectParent.right - rectParent.left) - nWidth) / 2 + rectParent.left;
		int nY = ((rectParent.bottom - rectParent.top) - nHeight) / 2 + rectParent.top;

		int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

		// make sure that the dialog box never moves outside of the screen
		if (nX < 0) nX = 0;
		if (nY < 0) nY = 0;
		if (nX + nWidth > nScreenWidth) nX = nScreenWidth - nWidth;
		if (nY + nHeight > nScreenHeight) nY = nScreenHeight - nHeight;

		MoveWindow(hwndWindow, nX, nY, nWidth, nHeight, FALSE);

		return TRUE;
	}

	return FALSE;
}
