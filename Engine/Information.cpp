#include "Information.h"

const char* MafiaBar::Engine::Information::Information::GetUsername() { return getenv("USERNAME"); }

const char* MafiaBar::Engine::Information::Information::GetOSType() { return getenv("OS"); }

const char* MafiaBar::Engine::Information::Information::GetComputerName() { return getenv("COMPUTERNAME"); }

const char* MafiaBar::Engine::Information::Information::GetTempFolder() { return getenv("TEMP"); }

const char* MafiaBar::Engine::Information::Information::GetUserProfileFolder() { return getenv("USERPROFILE"); }

const char* MafiaBar::Engine::Information::Information::GetDefaultProgramDataFolder() { return getenv("ALLUSERSPROFILE"); }

const char* MafiaBar::Engine::Information::OS::WindowsName() { return Registery.RegistryRead(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"ProductName", REG_SZ); }

const char* MafiaBar::Engine::Information::OS::WindowsType() { return Registery.RegistryRead(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"InstallationType", REG_SZ); }

const char* MafiaBar::Engine::Information::OS::WindowsOwner() { return Registery.RegistryRead(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"RegisteredOwner", REG_SZ); }

const char* MafiaBar::Engine::Information::OS::Edition() { return Registery.RegistryRead(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"EditionID", REG_SZ); }

const char* MafiaBar::Engine::Information::OS::Branch() { return Registery.RegistryRead(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"BuildBranch", REG_SZ); }

const int MafiaBar::Engine::Information::OS::Build() { return std::stoi(Registery.RegistryRead(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", L"CurrentBuildNumber", REG_SZ)); }

MafiaBar::Engine::Information::Hardware::Hardware()
{
	::GetSystemInfo(&SystemInfo);

	IDXGIAdapter* Adaptor = nullptr;
	IDXGIFactory* Factory = nullptr;
	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));
	
	Factory->EnumAdapters(0, &Adaptor);
	Adaptor->GetDesc(&Adaptor_Desc);

	Factory->Release(); Factory = 0;
	Adaptor->Release(); Adaptor = 0;
}

MafiaBar::Engine::Information::Hardware::~Hardware() { }

const char* MafiaBar::Engine::Information::Hardware::CPUName() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::CPUIdentifier() { return getenv("PROCESSOR_IDENTIFIER"); }

DWORD MafiaBar::Engine::Information::Hardware::CPUType() { return SystemInfo.dwProcessorType; }

DWORD MafiaBar::Engine::Information::Hardware::CPUProcessorsCount() { return SystemInfo.dwNumberOfProcessors; }


const char* MafiaBar::Engine::Information::Hardware::GPUName() 
{ 
	static char Name[MAX_PATH]{};
	wcstombs(Name, Adaptor_Desc.Description, MAX_PATH);
	return Name;
}

unsigned int MafiaBar::Engine::Information::Hardware::GPUMemorySize() { return ((Adaptor_Desc.DedicatedVideoMemory / 1024) / 1024); }

DWORD MafiaBar::Engine::Information::Hardware::GPUVendorID() { return Adaptor_Desc.VendorId; }

DWORD MafiaBar::Engine::Information::Hardware::GPUDeviceID() { return Adaptor_Desc.DeviceId; }


const char* MafiaBar::Engine::Information::Hardware::BoardManufacturer() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardManufacturer", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::BoardProduct() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardProduct", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::BIOSVendor() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BIOSVendor", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::BIOSVersion() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System", L"SystemBiosVersion", REG_SZ); }

SYSTEM_INFO MafiaBar::Engine::Information::Hardware::GetSystemInfo() const { return SystemInfo; }
