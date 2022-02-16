#include "Window.h"

/*--------------------------------------Initialie The Mafia Bar Engine Window Global Ojbect For Use In Everywhere--------------------------------------*/
Window* window = nullptr;

/*--------------------------------------The Mafia Bar Engine Window Menus ID Definitions--------------------------------------*/
#define FILE_QUIT 20091
#define FILE_TAKE_SCREENSHOT 20092

/*--------------------------------------Initializing The Mafia Bar Engine Window--------------------------------------*/
Window::Window(const char* WinTitle, int width, int height, bool fullscreen)
{
	if(FindWindowA(NULL, WinTitle) == NULL)
	{
		this->RegisterWindowClass();

		this->Width = width;
		this->Height = height;
		this->AppName = WinTitle;

		this->handle = CreateWindowExA(WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT,
			"Mafia Bar", //Window Class name
			WinTitle, //Windows Title
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows Styles
			0, //Window X Position
			0, //Windows Y Posiontion
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

		graphics = std::make_unique<MafiaBar::Engine::Graphics::Graphics>(handle, Width, Height);

		//Setting Fullscreen
		if (fullscreen == true)
		{
			if (graphics->GetSwap()->SetFullscreenState(TRUE, nullptr) == S_OK) { this->fullscreen = true; }
			else { log.Log("Setting Fullscreen On, Using SwapChain D3D11", "Failed"); }
		}
		if (fullscreen == false)
		{
			if (graphics->GetSwap()->SetFullscreenState(false, nullptr) == S_OK) { this->fullscreen = false; }
			else { log.Log("Setting Fullscreen Off, Using SwapChain D3D11", "Failed"); }
		}

		window = this;
	}
	else { MafiaBar::Engine::Logger::Message("Mafia Bar Engine", "One of the Instance of Mafia Bar Engine is running, first close it and run the program again", MB_ICONERROR); }
}
/*--------------------------------------Creates The Window Class/Style--------------------------------------*/
void Window::RegisterWindowClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	
	wcex.hCursor = LoadCursorA(hInstance, MAKEINTRESOURCEA(103));

	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wcex.hIcon = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));
	wcex.hIconSm = static_cast<HICON>(LoadImage(hInstance, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));;

	wcex.lpszClassName = L"Mafia Bar";

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = hInstance;

	wcex.lpfnWndProc = WindowProcedureSetup;

	RegisterClassEx(&wcex);
}
/*--------------------------------------WNDPROC For Mafia Bar Engine Window--------------------------------------*/
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
LRESULT __stdcall Window::WindowProcedureSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WindowProcedureThunk));

		return pWnd->WindowProcedure(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT __stdcall Window::WindowProcedureThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->WindowProcedure(hWnd, msg, wParam, lParam);
}

LRESULT Window::WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		/*------------------------------ Console Window Events ------------------------------*/
		case WM_CTLCOLORSTATIC:
		{
			HDC hdc = (HDC)wParam;
			SetBkMode(hdc, TRANSPARENT);
			console.SetTextColor(0, 0, 255);
			SetTextColor(hdc, RGB(std::get<0>(console.GetColors()), std::get<1>(console.GetColors()), std::get<2>(console.GetColors())));
			return (LRESULT)GetStockObject(BLACK_BRUSH);
		}
		/*------------------------------ Keyboard Events ------------------------------*/
		case WM_KEYDOWN:
		{
			keyboard.OnKeyPressed(static_cast<unsigned char>(wParam));
			break;
		}
		case WM_KEYUP:
		{
			keyboard.OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		}
		case WM_CHAR:
		{
			keyboard.OnChar(static_cast<char>(wParam));
			break;
		}
		/*------------------------------ Mouse Events ------------------------------*/
		case WM_MOUSEMOVE:
		{
			const POINTS pt = MAKEPOINTS(lParam); //Stroing The Mouse Moved Position
			mouse.OnMouseMove(pt.x, pt.y);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnLeftPressed(pt.x, pt.y);
			printf("%d, %d\n", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		}
		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnLeftReleased(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnRightPressed(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			mouse.OnRightReleased(pt.x, pt.y);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) { mouse.OnWheelUp(pt.x, pt.y); }
			else if (GET_WHEEL_DELTA_WPARAM(wParam < 0)) { mouse.OnWheelDown(pt.x, pt.y); }
			break;
		}
		/*------------------------------Mafia Bar Engine Window Events ------------------------------*/
		case WM_CREATE:
		{
			AddMenus(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_CLOSE:
		{
			if (MessageBoxA(hWnd, "Are you sure you want to quit?", AppName, MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
			{
				PostQuitMessage(0);
				return 0;
			}
			return 0;
		}
		case WM_HOTKEY:
		{
			if (wParam == hotkey.ESC)
			{
				if (focus == true)
				{
					graphics->GetSwap()->SetFullscreenState(FALSE, NULL);
					fullscreen = false;
				}
			}
			if (wParam == hotkey.QUIT)
			{
				if (focus == true)
				{
					PostQuitMessage(0);
					return 0;
				}
			}
			if (wParam == hotkey.FULLSCREEN)
			{
				if (focus == true)
				{
					graphics->GetSwap()->SetFullscreenState(TRUE, NULL);
					fullscreen = true;
				}
			}
			break;
		}
		case WM_COMMAND:
		{
			switch (wParam)
			{
			case FILE_QUIT:
				PostQuitMessage(0);
				return 0;
				break;
			case FILE_TAKE_SCREENSHOT:
				ScreenShot();
				break;
			default:
				break;
			}
			break;
		}
		case WM_SETFOCUS:
		{
			focus = true;
			break;
		}
		case WM_KILLFOCUS:
		{
			focus = false;
			break;
		}
		/*
		case WM_NCCALCSIZE:
		{
			LPNCCALCSIZE_PARAMS ncParams = (LPNCCALCSIZE_PARAMS)lParam;
			ncParams->rgrc[0].top += 4;
			ncParams->rgrc[0].left += 4;
			ncParams->rgrc[0].bottom -= 4;
			ncParams->rgrc[0].right -= 4;
			return 0;
		}
		case WM_NCPAINT:
		{
			RECT rect;
			GetWindowRect(hWnd, &rect);
			HRGN region = NULL;
			if (wParam == NULLREGION) {
				region = CreateRectRgn(rect.left, rect.top, rect.right, rect.bottom);
			}
			else {
				HRGN copy = CreateRectRgn(0, 0, 0, 0);
				if (CombineRgn(copy, (HRGN)wParam, NULL, RGN_COPY)) {
					region = copy;
				}
				else {
					DeleteObject(copy);
				}
			}

			HDC dc = GetDCEx(hWnd, region, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE);
			if (!dc && region) {
				DeleteObject(region);
			}
			HPEN pen = CreatePen(PS_INSIDEFRAME, 4, RGB(0, 0, 0));
			HGDIOBJ old = SelectObject(dc, pen);
			Rectangle(dc, 0, 0, Width, Height);
			SelectObject(dc, old);
			ReleaseDC(hWnd, dc);
			DeleteObject(pen);
			return 0;
		}
		case WM_NCACTIVATE:
		{
			RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW);
			return 0;
		}
		*/	
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
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
/*--------------------------------------Window Utils Functions--------------------------------------*/
void Window::SetWindowTransparency(std::uint8_t Transperancy)
{
	long wAttr = GetWindowLong(handle, GWL_EXSTYLE);
	SetWindowLong(handle, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
	SetLayeredWindowAttributes(handle, 0, Transperancy, 0x02);
}
void Window::SetWindowAsOverlay() { ::SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); }
void Window::AddMenus(HWND hwnd)
{
	WindowMenus = CreateMenu();
	HMENU hFileMenu = CreateMenu();

	AppendMenuA(WindowMenus, MF_POPUP, (UINT_PTR)hFileMenu, "File");
		AppendMenuA(hFileMenu, MF_STRING, FILE_TAKE_SCREENSHOT, "Take a Screenshot");
		AppendMenuA(hFileMenu, MF_SEPARATOR, NULL, NULL);
		AppendMenuA(hFileMenu, MF_STRING, FILE_QUIT, "Quit");

	SetMenu(hwnd, WindowMenus);
}
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

void Window::Restart()
{
	log.Log("Mafia Bar Engine", "The Application Have Restarted");
	ShellExecuteA(handle, "open", GetProgramFullPath(), NULL, NULL, SW_RESTORE);
	PostQuitMessage(0);
	ExitProcess(0);
}

void Window::Exit(int ExitCode)
{
	PostQuitMessage(ExitCode);
	if (this->handle != NULL)
	{
		UnregisterClassA("Mafia Bar", this->hInstance);
		DestroyWindow(handle);
	}

}
