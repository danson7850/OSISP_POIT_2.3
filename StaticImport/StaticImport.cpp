#include <iostream>
#include <Windows.h>

extern "C" __declspec(dllimport) void __cdecl ReplaceString(
	DWORD pid,
	const char* srcStr,
	const char* repStr);

int main()
{
	DWORD pid = GetCurrentProcessId();

	const char srcStr[] = "Old String";
	const char repStr[] = "New String";

	ReplaceString(pid, srcStr, repStr);

	std::cout << srcStr << "\n";
	std::cin.get();
}
