#pragma once

#define USERNAME getenv("USERNAME")
#define COMPUTERNAME getenv("COMPUTERNAME")

namespace MafiaBar
{
	class Information
	{
	};
	struct EXP_ENGINE System_Information : public Information
	{

		char* CPU_NAME();
		char* CPU_IDEN();
		DWORD CPU_NUMOfProcess(SYSTEM_INFO& siSysInfo);
		DWORD CPU_TYPE(SYSTEM_INFO& siSysInfo);
		char* GPU_NAME();
		char* BaseBoardManufacturer();
		char* BaseBoardProduct();
		char* BIOSVendor();
		char* BIOSVersion();
		SYSTEM_INFO siSysInfo;
	};
	struct EXP_ENGINE OS_Information : public Information
	{
		int Build_Version();
		char* Window_Version();
		char* Edition();
	    char* Display_Version();
		char* Build_Branch();
	};
}