#pragma once
#include "Engine.h"

#include "WinRegistery.h"

namespace MafiaBar
{
	namespace Engine
	{
		namespace Information
		{
			class EXP_ENGINE Information
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
			class EXP_ENGINE OS : public Information
			{
			public:
				const char* WindowsName();
				const char* WindowsType();
				const char* WindowsOwner();
				const char* Edition();
				const char* Branch();
				const int Build();
			};
			class EXP_ENGINE Hardware : public Information
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
				const char* GPUDeviceName();
				const char* GPUDriverName();
				DWORD GPUVendorID();
				DWORD GPUDeviceID();
				int GetGraphicCardCount();
				//BIOS and Board Informations
				const char* BoardManufacturer();
				const char* BoardProduct();
				const char* BIOSVendor();
				const char* BIOSVersion();
				//Getter Functions
				SYSTEM_INFO GetSystemInfo() const;
			private:
				SYSTEM_INFO SystemInfo;
				IDirect3D9* d3dobject = Direct3DCreate9(D3D_SDK_VERSION);
				D3DADAPTER_IDENTIFIER9* GraphicsAdaptors = (D3DADAPTER_IDENTIFIER9*)malloc(sizeof(D3DADAPTER_IDENTIFIER9) * GetGraphicCardCount());
			};
		}
	}
}