#include "Utilities.h"

MafiaBar::Utilities::Time::Time(const char* Process_Describ)
    : start(std::chrono::high_resolution_clock::now()), label(Process_Describ)  
{ 
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

MafiaBar::Utilities::Time::Time() { last = std::chrono::steady_clock::now(); }

void MafiaBar::Utilities::Time::Start(const char* Process_Describ)
{
    start = std::chrono::high_resolution_clock::now();
    label = Process_Describ;
    printf_s("Timer Started\t%s\n", Process_Describ);
    last = std::chrono::steady_clock::now();
}

void MafiaBar::Utilities::Time::End()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;
    printf("The Procces: %s Took: %fms\n", label, ms);
}

float MafiaBar::Utilities::Time::Mark()
{
    const auto old = last;
    last = std::chrono::steady_clock::now();
    const std::chrono::duration<float> frameTime = last - old;
    return frameTime.count();
}

float MafiaBar::Utilities::Time::Peek() const { return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count(); }

const char* MafiaBar::Utilities::Time::GetCurrentDateAndTime()
{
    time_t rawtime;
    time(&rawtime);
    return ctime(&rawtime);
}

constexpr MB_ENGINE_API const DWORD MafiaBar::Utilities::GetProcessID(HWND Handle)
{
    if (Handle == NULL) { return GetCurrentProcessId(); }
    else
    {
        DWORD ProcessID = 0;
        GetWindowThreadProcessId(Handle, &ProcessID);
        return ProcessID;
    }
}

MB_ENGINE_API char* MafiaBar::Utilities::GetProgramFullPath(HINSTANCE hInstance)
{
    static char pathtofile[MAX_PATH]{};
    GetModuleFileNameA(hInstance, pathtofile, sizeof(pathtofile));
    return pathtofile;
}

MB_ENGINE_API void MafiaBar::Utilities::SetWindowTransparency(HWND Handle, uint8_t Transperancy)
{
    long wAttr = GetWindowLong(Handle, GWL_EXSTYLE);
    SetWindowLong(Handle, GWL_EXSTYLE, wAttr | WS_EX_LAYERED);
    SetLayeredWindowAttributes(Handle, 0, Transperancy, 0x02);
}

MB_ENGINE_API void MafiaBar::Utilities::SetWindowAsOverlay(HWND Handle) { ::SetWindowPos(Handle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW); }

MB_ENGINE_API BOOL MafiaBar::Utilities::CenterWindow(HWND Handle, int Width, int Height)
{
    if (Width == 0 && Height == 0)
    {
        RECT rect;
        if (GetWindowRect(Handle, &rect) == TRUE)
        {
            Width = rect.right - rect.left;
            Height = rect.bottom - rect.top;
        }
    }

    int CenterScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - Width / 2;
    int CenterScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - Height / 2;

    RECT wr{};
    wr.left = CenterScreenX;
    wr.top = CenterScreenY;
    wr.right = wr.left + Width;
    wr.bottom = wr.top + Height;
    if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, false) == false) { return false; }

    if (MoveWindow(Handle, wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, true) == false) { return false; }

    return true;
}

MB_ENGINE_API bool MafiaBar::Utilities::IsWindows11OrGreater()
{
    HMODULE DLLModule = LoadLibraryA("Ntdll.dll");
    typedef NTSTATUS(CALLBACK* RTLGETVERSION) (PRTL_OSVERSIONINFOW lpVersionInformation);
    RTLGETVERSION pRtlGetVersion;
    pRtlGetVersion = (RTLGETVERSION)GetProcAddress(DLLModule, "RtlGetVersion");
    RTL_OSVERSIONINFOW ovi = { 0 };
    ovi.dwOSVersionInfoSize = sizeof(ovi);
    NTSTATUS ntStatus = pRtlGetVersion(&ovi);
    if (ntStatus == 0)
    {
        if (ovi.dwBuildNumber >= 22000)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

MB_ENGINE_API void MafiaBar::Utilities::TakeScreenshot(IDXGISwapChain* SwapChain, ID3D11DeviceContext* DeviceContext, HWND WindowHandle)
{
    OPENFILENAMEW ofn{};
    wchar_t FileName[260];
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = WindowHandle;
    ofn.lpstrFile = FileName;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(FileName);
    ofn.lpstrFilter = L"JPEG Format\0*.jpg\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST;

    if (GetSaveFileNameW(&ofn) == TRUE)
    {
        ID3D11Texture2D* BackBuffer = nullptr;
        if (SwapChain != nullptr && DeviceContext != nullptr)
        {
            MB_EXCEPTION(SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer)));
            MB_EXCEPTION(DirectX::SaveWICTextureToFile(DeviceContext, BackBuffer, GUID_ContainerFormatJpeg, FileName));
        }
        BackBuffer->Release();
        BackBuffer = 0;
    }
}

MB_ENGINE_API MessageBoxFlag MafiaBar::Utilities::MessageBox(const char* Caption, const char* Text, MessageBoxFlag Flags, ImGuiWindowFlags ImGuiFlags)
{
    //Run the ImGui::Popup Function only once
    static bool FunctionOnce = [Caption]()
    {
        ImGui::OpenPopup(Caption, ImGuiPopupFlags_::ImGuiPopupFlags_NoOpenOverExistingPopup);
        return true;
    } ();

    bool Open = true;
    if (ImGui::BeginPopupModal(Caption, &Open, ImGuiFlags))
    {
        ImGui::Text(Text);
        if (Flags == OK_BUTTON)
        {
            if (ImGui::Button("OK"))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return OK_BUTTON;
            }
        }
        else if (Flags == CANCEL_BUTTON)
        {
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return CANCEL_BUTTON;
            }
        }
        else if (Flags == CLOSE_BUTTON)
        {
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return CLOSE_BUTTON;
            }
        }
        else if (Flags && (OK_BUTTON | CLOSE_BUTTON | CANCEL_BUTTON))
        {
            if (ImGui::Button("OK"))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return OK_BUTTON;
            }
            if (ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return CANCEL_BUTTON;
            }
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
                return CLOSE_BUTTON;
            }
            else
            {
                ImGui::EndPopup();
                return false;
            }
        }
        ImGui::EndPopup();
    }

}