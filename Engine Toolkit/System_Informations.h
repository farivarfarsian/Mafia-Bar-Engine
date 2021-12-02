#pragma once
#include "../Mafia Bar Engine/pch.h"
#include "Engine_Toolkit.h"

#ifdef _WIN32
#ifdef _WIN64
#define PLATFORM "Windows 64 bit"
#else 
#define PLATFORM "Windows 32 bit"
#endif
#elif defined __linux
#define PLATFORM "Linux"
#elif defined __macosx
#define PLATFORM "MacOSX"
#else
#define PLATFORM "Others"
#endif

#define USERNAME getenv("USERNAME")
#define COMPUTERNAME getenv("COMPUTERNAME")

namespace Engine
{
	/*
	* Tempalte of Getting All System Information
		Engine::System_Information sys;
	std::cout << "--------------------System Information--------------------" << std::endl
		<< "CPU Name: " << sys.CPU_NAME() << std::endl << "CPU Identifier: " << sys.CPU_IDEN() << std::endl
		<< "Number of CPU Processers: " << sys.CPU_NUMOfProcess(sys.siSysInfo) << std::endl << "CPU Type: " << sys.CPU_TYPE(sys.siSysInfo) << std::endl
		<< "GPU Name: " << sys.GPU_NAME() << std::endl << "MotherBoard: " << sys.BaseBoardManufacturer() << std::endl
		<< "Motherboard Product: " << sys.BaseBoardProduct() << std::endl << "BIOS Vendor: " << sys.BIOSVendor() << std::endl
		<< "BIOS Version: " << sys.BIOSVersion() << std::endl
		<< "--------------------OS Information------------------------" << std::endl
		<< "Window Platform: " << PLATFORM << std::endl << "Window Version: " << Engine::OS_Information::Window_Version() << std::endl
		<< "Window Edition: " << Engine::OS_Information::Edition() << std::endl << "Display Version: " << Engine::OS_Information::Display_Version() << std::endl
		<< "Current Build Number: " << Engine::OS_Information::Build_Version() << std::endl << "Build Branch: " << Engine::OS_Information::Build_Branch() << std::endl
		<< "--------------------General Information-------------------" << std::endl
		<< "Execution File Name: " << Engine::General_Information::Exucate_Name() << "\t"
		<< "Script File Name: " << Engine::General_Information::Script_Name(__FILE__) << std::endl
		<< "Window Title: " << Engine::General_Information::Window_Title(rw.handle) << "\t\t\t"
		<< "Process ID: " << Engine::General_Information::ProcessID() << "\t" << "Username: " << Engine::General_Information::Username() << std::endl
		<< "----------------------------------------------------------" << std::endl;
	* Still Not Optimized And In Progress
	*/
	struct EXP_ENGINE System_Information
	{
		SYSTEM_INFO siSysInfo;
		char* CPU_NAME();
		char* CPU_IDEN();
		DWORD CPU_NUMOfProcess(SYSTEM_INFO& siSysInfo);
		DWORD CPU_TYPE(SYSTEM_INFO& siSysInfo);
		char* GPU_NAME();
		char* BaseBoardManufacturer();
		char* BaseBoardProduct();
		char* BIOSVendor();
		char* BIOSVersion();
	};
	struct EXP_ENGINE OS_Information
	{
		static int Build_Version();
		static char* Window_Version();
		static char* Edition();
		static char* Display_Version();
		static char* Build_Branch();
	};
	struct EXP_ENGINE General_Information
	{
		static std::string Exucate_Name();
		static std::string Script_Name(const char* script_macro_file);
		static char* Window_Title(HWND handle);
	};
}