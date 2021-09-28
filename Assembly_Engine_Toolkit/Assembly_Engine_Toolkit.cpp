#include <SDKDDKVer.h>
#include <stdio.h>
#include <Windows.h>


// External assembly functions we want to call from here
extern "C"
{
	void hello_world_asm();
	void Main();
};


int main()
{
	hello_world_asm();
	return 0;
}