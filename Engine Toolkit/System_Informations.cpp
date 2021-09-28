#include "System_Informations.h"

char* Engine::System_Information::CPU_NAME()
{
	return std::move(Engine::registry_read(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", REG_SZ));
}

char* Engine::System_Information::CPU_IDEN()
{
	return std::move(Engine::registry_read(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"Identifier", REG_SZ));
}

DWORD Engine::System_Information::CPU_NUMOfProcess(SYSTEM_INFO& siSysInfo)
{
	GetSystemInfo(&siSysInfo);
	return siSysInfo.dwNumberOfProcessors;
}

DWORD Engine::System_Information::CPU_TYPE(SYSTEM_INFO& siSysInfo)
{
	GetSystemInfo(&siSysInfo);
	return siSysInfo.dwProcessorType;
}

char* Engine::System_Information::GPU_NAME()
{
	return std::move(Engine::registry_read(L"SYSTEM\\CurrentControlSet\\Control\\Video\\{21860B0B-F3F2-11EB-AD49-806E6F6E6963}\\0000", L"DriverDesc", REG_SZ));
}

char* Engine::System_Information::BaseBoardManufacturer()
{
	return std::move(Engine::registry_read(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardManufacturer", REG_SZ));
}

char* Engine::System_Information::BaseBoardProduct()
{
	return std::move(Engine::registry_read(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardProduct", REG_SZ));
}

char* Engine::System_Information::BIOSVendor()
{
	return std::move(Engine::registry_read(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BIOSVendor", REG_SZ));
}

char* Engine::System_Information::BIOSVersion()
{
	return std::move(Engine::registry_read(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BIOSVersion", REG_SZ));
}

int Engine::OS_Information::Build_Version()
{
	return std::move(atoi((Engine::registry_read(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"CurrentBuild", REG_SZ))));
}

char* Engine::OS_Information::Window_Version()
{
	if (Build_Version() >= 22000)
	{
		return (char*)"Windows 11";
	}
	else
	{
		return std::move(Engine::registry_read(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName", REG_SZ));
	}
}

char* Engine::OS_Information::Edition()
{
	return std::move(Engine::registry_read(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"EditionID", REG_SZ));
}

char* Engine::OS_Information::Display_Version()
{
	return std::move(Engine::registry_read(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"DisplayVersion", REG_SZ));
}

char* Engine::OS_Information::Build_Branch()
{
	return std::move(Engine::registry_read(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"BuildBranch", REG_SZ));
}

std::string Engine::General_Information::Exucate_Name()
{
	char ExecFullPath[MAX_PATH];
	GetModuleFileNameA(nullptr, ExecFullPath, MAX_PATH);
	std::string file_exec = std::string(ExecFullPath);
	size_t lenghg = file_exec.find_last_of('\\');
	return file_exec.substr(lenghg + 1);
}

std::string Engine::General_Information::Script_Name(const char* script_macro_file)
{
	std::string FileScript = script_macro_file;
	size_t lenghg = FileScript.find_last_of('\\');
	return FileScript.substr(lenghg + 1);
}

char* Engine::General_Information::Window_Title(HWND handle)
{
	static char wnd_title[MAX_NAME_STRING];
	GetWindowTextA(handle, wnd_title, sizeof(wnd_title));
	return std::move(wnd_title);
}

DWORD Engine::General_Information::ProcessID()
{
	return GetCurrentProcessId();
}