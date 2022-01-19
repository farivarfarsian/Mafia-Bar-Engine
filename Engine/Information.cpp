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
	for (int i = 0; i < GetGraphicCardCount(); i++) { d3dobject->GetAdapterIdentifier(i, 0, &(GraphicsAdaptors[i])); }
}

MafiaBar::Engine::Information::Hardware::~Hardware() { d3dobject->Release(); }

const char* MafiaBar::Engine::Information::Hardware::CPUName() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", L"ProcessorNameString", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::CPUIdentifier() { return getenv("PROCESSOR_IDENTIFIER"); }

DWORD MafiaBar::Engine::Information::Hardware::CPUType() { return SystemInfo.dwProcessorType; }

DWORD MafiaBar::Engine::Information::Hardware::CPUProcessorsCount() { return SystemInfo.dwNumberOfProcessors; }

const char* MafiaBar::Engine::Information::Hardware::GPUName() { return GraphicsAdaptors->Description; }

const char* MafiaBar::Engine::Information::Hardware::GPUDeviceName() { return GraphicsAdaptors->DeviceName; }

const char* MafiaBar::Engine::Information::Hardware::GPUDriverName() { return GraphicsAdaptors->Driver; }

DWORD MafiaBar::Engine::Information::Hardware::GPUVendorID() { return GraphicsAdaptors->VendorId; }

DWORD MafiaBar::Engine::Information::Hardware::GPUDeviceID() { return GraphicsAdaptors->DeviceId; }

int MafiaBar::Engine::Information::Hardware::GetGraphicCardCount() { return d3dobject->GetAdapterCount(); }

const char* MafiaBar::Engine::Information::Hardware::BoardManufacturer() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardManufacturer", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::BoardProduct() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BaseBoardProduct", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::BIOSVendor() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System\\BIOS", L"BIOSVendor", REG_SZ); }

const char* MafiaBar::Engine::Information::Hardware::BIOSVersion() { return Registery.RegistryRead(L"HARDWARE\\DESCRIPTION\\System", L"SystemBiosVersion", REG_SZ); }

SYSTEM_INFO MafiaBar::Engine::Information::Hardware::GetSystemInfo() const { return SystemInfo; }
