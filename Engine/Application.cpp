#include "Application.h"

void MafiaBar::Engine::Application::Initialize(const char* Title, const char* ClassName, int Width, int Height, bool Fullscreen, int IconResourceFileID, int CursorResourceFileID)
{
	this->ApplicationClassName = ClassName;
	this->Width = Width;
	this->Height = Height;
	ApplicationTitle = Title;

	WNDCLASSEX wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursorA(ApplicationInstance, MAKEINTRESOURCEA(CursorResourceFileID));

	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);

	wcex.hIcon = static_cast<HICON>(LoadImage(ApplicationInstance, MAKEINTRESOURCE(IconResourceFileID), IMAGE_ICON, 32, 32, 0));
	wcex.hIconSm = static_cast<HICON>(LoadImage(ApplicationInstance, MAKEINTRESOURCE(IconResourceFileID), IMAGE_ICON, 16, 16, 0));;

	wchar_t ApplicationClassNameW[100];
	mbstowcs(ApplicationClassNameW, ApplicationClassName, 100);
	wcex.lpszClassName = ApplicationClassNameW;

	wcex.lpszMenuName = nullptr;

	wcex.hInstance = ApplicationInstance;

	wcex.lpfnWndProc = WindowProcedureSetup;

	RegisterClassExW(&wcex);

	//This feature has been disabled for now, there is problem with the Restart function.
	if (OneApplicationGuard == true && FindWindowA(NULL, ApplicationTitle) != NULL)
	{
		MafiaBar::Engine::Engine::Get().GetLogger().Message("Mafia Bar Engine", "One of the Instance of Mafia Bar Engine is aleady running, first close it and run the program again", MB_ICONERROR);
		Exit(ApplicationErrorCodes::TRYING_TO_RUN_MULTIPLE_INSTANCES_OF_APPLICATION);
		return;
	}

	BeforeInitialize();

	ApplicationHandle = CreateWindowExA(WS_EX_ACCEPTFILES | WS_EX_TRANSPARENT,
		ApplicationClassName, //Window Class name
		Title, //Windows Title
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows Styles
		0, //Window X Position
		0, //Window Y Posiontion
		Width, //Window Width
		Height, //Window Height
		nullptr, //Handle of Parent of this Windows
		nullptr, //Handle to menu or Child Windows Identifier
		ApplicationInstance, //handle to the instance of module to be used with this class
		this); //Param to Create Window

	if (ApplicationHandle == NULL) { MB_EXCEPTION(GetLastError()); }

	//Getting Dark/Light Mode Enabled Boolean, 
	//Note: Be aware of that If you want to check that If the Dark mode is enabled you should do it like this: !LightModeEnabled .
	unsigned long DarkModeEnabledSize = sizeof(LightModeEnabled);
	MB_EXCEPTION(RegGetValueA(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", "AppsUseLightTheme", RRF_RT_DWORD, NULL, &LightModeEnabled, &DarkModeEnabledSize));
;
	//Enabling Immersive Dark Mode for Mafia Bar Engine,
	//Note: Does work for both Windows 10 and 11 but for using this feature and being able to compile the code, you have to use the Windows 11 SDK(10.0.22000.0v)
	int isDarkModeEnabled{ !LightModeEnabled };
	HRESULT DEBUGCODE = DwmSetWindowAttribute(ApplicationHandle, DWMWA_USE_IMMERSIVE_DARK_MODE, &isDarkModeEnabled, sizeof(isDarkModeEnabled));
	#if IS_DEBUG
		MB_EXCEPTION(DEBUGCODE);
	#endif

	//Creating Graphics And Scene
	MafiaBar::Engine::Engine::Get().CreateGraphicsAndScene(ApplicationHandle, Fullscreen, true);

	//Creating the Win32 Console
	AllocConsole(); FILE* fp;
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	SetConsoleTitleA("Mafia Bar Engine: Debug Console");

	SetFocus(ApplicationHandle);
	ShowWindow(ApplicationHandle, SW_SHOW);

	//Setting Fullscreen
	if (IsFullScreen == true)
	{
		if (MafiaBar::Engine::Engine::Get().GetGraphics().GetSwap()->SetFullscreenState(true, nullptr) == S_OK) { IsFullScreen = true; }
		else { MafiaBar::Engine::Engine::Get().GetLogger().Log("Setting Fullscreen On, Using SwapChain D3D11", "Failed"); }
	}
	else if (IsFullScreen == false)
	{
		if (MafiaBar::Engine::Engine::Get().GetGraphics().GetSwap()->SetFullscreenState(false, nullptr) == S_OK) { IsFullScreen = false; }
		else { MafiaBar::Engine::Engine::Get().GetLogger().Log("Setting Fullscreen Off, Using SwapChain D3D11", "Failed"); }
	}

	AfterInitialize();
}

void MafiaBar::Engine::Application::Restart()
{
	PROCESS_INFORMATION processInformation{};
	STARTUPINFOA startupInfo{};
	startupInfo.cb = sizeof(startupInfo);
	if (CreateProcessA(NULL, GetCommandLineA(), NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, NULL, NULL, &startupInfo, &processInformation) == TRUE)
	{
		MafiaBar::Engine::Engine::Get().GetLogger().Log("Restarting the application", "Application restarted");
		PostQuitMessage(0);
		ExitProcess(0);
		Sleep(60);
		ApplicationID = processInformation.dwProcessId;
		CloseHandle(processInformation.hProcess);
		CloseHandle(processInformation.hThread);
	}
	else { MB_EXCEPTION(GetLastError()); };
}

void MafiaBar::Engine::Application::Exit(int ExitCode)
{
	PostQuitMessage(ExitCode);
	if (ApplicationHandle != NULL)
	{
		UnregisterClassA(ApplicationClassName, ApplicationInstance);
		DestroyWindow(ApplicationHandle);
	}
}

std::optional<int> MafiaBar::Engine::Application::ProcessMessages()
{	
	MSG msg{};
	while (PeekMessageA(&msg, ApplicationHandle, 0,0,PM_REMOVE))
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

LRESULT __stdcall MafiaBar::Engine::Application::WindowProcedureSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		Application* const pWnd = static_cast<Application*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Application::WindowProcedureThunk));

		return pWnd->WindowProcedure(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT __stdcall MafiaBar::Engine::Application::WindowProcedureThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Application* const pWnd = reinterpret_cast<Application*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->WindowProcedure(hWnd, msg, wParam, lParam);
}

LRESULT MafiaBar::Engine::Application::WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	/*------------------------------ Keyboard Events ------------------------------*/
	case WM_KEYDOWN:
	{
		MafiaBar::Engine::Engine::Get().GetKeyboard().OnKeyPressed(static_cast<unsigned char>(wParam));
		
		if (MafiaBar::Engine::Engine::Get().GetKeyboard().IsKeyPressed((unsigned char)VK_CONTROL) && MafiaBar::Engine::Engine::Get().GetKeyboard().IsKeyPressed((unsigned char)MafiaBar::Keyboard::Q))
		{
			Exit(ApplicationErrorCodes::SUCCEEDED);
		}
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
	/*------------------------------Mafia Bar Engine Events ------------------------------*/
	case WM_CREATE:
		OnCreate();
		break;
	case WM_CLOSE:
	{
		OnClose();
		if (MessageBoxA(hWnd, "Are you sure you want to quit?", ApplicationTitle, MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
		{
			PostQuitMessage(0);
			return 0;
		}
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SETFOCUS:
	{
		OnFocus();
		IsFocus = true;
		break;
	}
	case WM_KILLFOCUS:
	{
		IsFocus = false;
		break;
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void MafiaBar::Engine::Application::OnCreate()
{
}

void MafiaBar::Engine::Application::OnClose()
{
}

void MafiaBar::Engine::Application::BeforeInitialize()
{
}

void MafiaBar::Engine::Application::AfterInitialize()
{
}

void MafiaBar::Engine::Application::OnFocus()
{
}

void MafiaBar::Engine::Application::Setup()
{
}

void MafiaBar::Engine::Application::Frame()
{
}

int MafiaBar::Engine::Application::Present()
{
	Setup();

	while (true)
	{
		if (const auto ecode = ProcessMessages()) { return *ecode; }

		std::future<void> Frame = std::async(std::launch::async, &Application::Frame, this);
	}
}

MafiaBar::Engine::Application::~Application()
{
	if(ApplicationHandle != NULL)
	{
		UnregisterClassA(ApplicationClassName, ApplicationInstance);
		DestroyWindow(ApplicationHandle);
	}
}

constexpr HWND MafiaBar::Engine::Application::GetHandle() const { return ApplicationHandle; }

constexpr DWORD MafiaBar::Engine::Application::GetID() const { return ApplicationID; }

constexpr HINSTANCE MafiaBar::Engine::Application::GetInstance() const { return ApplicationInstance; }

constexpr int MafiaBar::Engine::Application::GetWidth() const { return Width; }

constexpr int MafiaBar::Engine::Application::GetHeight() const { return Height; }

constexpr const char* MafiaBar::Engine::Application::GetTitle() const { return ApplicationTitle; }

constexpr bool MafiaBar::Engine::Application::GetFullScreen() const { return IsFullScreen; }

constexpr bool MafiaBar::Engine::Application::GetFocus() const { return IsFocus; }
