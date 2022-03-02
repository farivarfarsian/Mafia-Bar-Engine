#pragma once
#include "Definitions.h"
#include "pch.h"

#include "WinRegistery.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Information
		{
			class MB_ENGINE_API Information
			{
			public:
				#undef GetComputerName //Undefing Microsoft Windows A/W Macro
				const char* GetUsername();
				const char* GetOSType();
				const char* GetComputerName();
				const char* GetTempFolder();
				const char* GetUserProfileFolder();
				const char* GetDefaultProgramDataFolder();
			protected:
				MafiaBar::Engine::Utilities::WinRegistery Registery;
			};
			class MB_ENGINE_API OS : public Information
			{
			public:
				const char* WindowsName();
				const char* WindowsType();
				const char* WindowsOwner();
				const char* Edition();
				const char* Branch();
				const int Build();
			};
			class MB_ENGINE_API Hardware : public Information
			{
			public:
				Hardware();
				~Hardware();
				//CPU Informations
				const char* CPUName();
				const char* CPUIdentifier();
				DWORD CPUType();
				DWORD CPUProcessorsCount();
				//GPU Informations
				const char* GPUName();
				unsigned int GPUMemorySize();
				DWORD GPUVendorID();
				DWORD GPUDeviceID();
				//BIOS and Board Informations
				const char* BoardManufacturer();
				const char* BoardProduct();
				const char* BIOSVendor();
				const char* BIOSVersion();
				//Getter Functions
				SYSTEM_INFO GetSystemInfo() const;
			private:
				SYSTEM_INFO SystemInfo;
				DXGI_ADAPTER_DESC Adaptor_Desc{};
			};
		}
	}
}