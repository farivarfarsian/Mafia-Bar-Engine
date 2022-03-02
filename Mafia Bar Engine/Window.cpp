#include "Window.h"

Window* window = nullptr;

/*--------------------------------------The Mafia Bar Engine Window Menus ID Definitions--------------------------------------*/
#define FILE_QUIT 20091
#define FILE_TAKE_SCREENSHOT 20092

/*--------------------------------------Initializing The Mafia Bar Engine Window--------------------------------------*/
Window::Window(const char* WinTitle, int width, int height, bool fullscreen)
{
	//if(FindWindowA(NULL, WinTitle) == NULL)
	//{
		this->RegisterWindowClass();

		this->Width = width;
		this->Height = height;
		this->AppName = WinTitle;

		this->handle = CreateWindowExA(WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT,
			"Mafia Bar", //Window Class name
			WinTitle, //Windows Title
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows Styles
			0, //Window X Position
			0, //Window Y Posiontion
			Width, //Window Width
			Height, //Window Height
			nullptr, //Handle of Parent of this Windows
			nullptr, //Handle to menu or Child Windows Identifier
			hInstance, //handle to the instance of module to be used with this class
			this); //Param to Create Window
		
		if (this->handle == NULL) {  }

		AllocConsole(); FILE* fp;
		freopen_s(&fp, "CONIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);

		SetConsoleTitleA("Mafia Bar Engine: Debug Console");

		CenterWindow(this->handle);
		SetFocus(this->handle);
		ShowWindow(this->handle, SW_SHOW);

		Engine::Get().CreateGraphics(this->handle, fullscreen, true);

		//Setting Fullscreen
		if (fullscreen == true)
		{
			if (Engine::Get().GetGraphics()->GetSwap()->SetFullscreenState(TRUE, nullptr) == S_OK) { this->fullscreen = true; }
			else { MafiaBar::Engine::Engine::Get().GetLogger().Log("Setting Fullscreen On, Using SwapChain D3D11", "Failed"); }
		}
		if (fullscreen == false)
		{
			if (Engine::Get().GetGraphics()->GetSwap()->SetFullscreenState(false, nullptr) == S_OK) { this->fullscreen = false; }
			else { MafiaBar::Engine::Engine::Get().GetLogger().Log("Setting Fullscreen Off, Using SwapChain D3D11", "Failed"); }
		}

		window = this;
	//}
	//else { MafiaBar::Engine::Logger::Message("Mafia Bar Engine", "One of the Instance of Mafia Bar Engine is running, first close it and run the program again", MB_ICONERROR); }
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
		/*------------------------------ Keyboard Events ------------------------------*/
		case WM_KEYDOWN:
		{		
			MafiaBar::Engine::Engine::Get().GetKeyboard().OnKeyPressed(static_cast<unsigned char>(wParam));
			break;
		}
		case WM_KEYUP:
		{
			MafiaBar::Engine::Engine::Get().GetKeyboard().OnKeyReleased(static_cast<unsigned char>(wParam));
			break;
		}
		case WM_CHAR:
		{
			MafiaBar::Engine::Engine::Get().GetKeyboard().OnChar(static_cast<char>(wParam));
			break;
		}
		/*------------------------------ Mouse Events ------------------------------*/
		case WM_MOUSEMOVE:
		{
			const POINTS pt = MAKEPOINTS(lParam); //Stroing The Mouse Moved Position
			MafiaBar::Engine::Engine::Get().GetMouse().OnMouseMove(pt.x, pt.y);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			MafiaBar::Engine::Engine::Get().GetMouse().OnLeftPressed(pt.x, pt.y);
			printf_s("%d, %d\n", GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			break;
		}
		case WM_LBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			MafiaBar::Engine::Engine::Get().GetMouse().OnLeftReleased(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			MafiaBar::Engine::Engine::Get().GetMouse().OnRightPressed(pt.x, pt.y);
			break;
		}
		case WM_RBUTTONUP:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			MafiaBar::Engine::Engine::Get().GetMouse().OnRightReleased(pt.x, pt.y);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			const POINTS pt = MAKEPOINTS(lParam);
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) { MafiaBar::Engine::Engine::Get().GetMouse().OnWheelUp(pt.x, pt.y); }
			else if (GET_WHEEL_DELTA_WPARAM(wParam < 0)) { MafiaBar::Engine::Engine::Get().GetMouse().OnWheelDown(pt.x, pt.y); }
			break;
		}
		/*------------------------------Mafia Bar Engine Window Events ------------------------------*/
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
					Engine::Get().GetGraphics()->GetSwap()->SetFullscreenState(FALSE, NULL);
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
					Engine::Get().GetGraphics()->GetSwap()->SetFullscreenState(TRUE, NULL);
					fullscreen = true;
				}
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
		#pragma region DrawingTheClientArea
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
		#pragma endregion
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
/*--------------------------------------Window Util Functions--------------------------------------*/

void Window::SetWindowTransparency(std::uint8_t Transperancy)
{
	long wAttr = GetWindowLong(handle, GWL_EXSTYLE);
	SetWindowLong(handle, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
	SetLayeredWindowAttributes(handle, 0, Transperancy, 0x02);
}

void Window::SetWindowAsOverlay() { ::SetWindowPos(handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); }

BOOL Window::CenterWindow(HWND hwndWindow)
{
	int CenterScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - Width / 2;
	int CenterScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - Height / 2;

	RECT wr{};
	wr.left = CenterScreenX;
	wr.top = CenterScreenY;
	wr.right = wr.left + Width;
	wr.bottom = wr.top + Height;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false) == false) { return false; }

	if (MoveWindow(hwndWindow, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, true) == false) { return false; }

	return true;
}

void Window::Restart()
{
	PROCESS_INFORMATION processInformation{};
	STARTUPINFOA startupInfo{};
	startupInfo.cb = sizeof(startupInfo);
	if (CreateProcessA(NULL, GetCommandLineA(), NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, NULL, NULL, &startupInfo, &processInformation) == TRUE)
	{
		Engine::Get().GetLogger().Log("Restarting the application", "Application restarted");
		PostQuitMessage(0);
		ExitProcess(0);
		Sleep(60);
		ProcessID = processInformation.dwProcessId;
		CloseHandle(processInformation.hProcess);
		CloseHandle(processInformation.hThread);
	}
	else { MB_EXCEPTION(GetLastError()); };
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
