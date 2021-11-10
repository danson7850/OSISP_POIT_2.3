#pragma once
#include <Windows.h>
#include <vector>

extern "C" __declspec(dllexport) void __cdecl ReplaceString(DWORD pid, const char* srcStr, const char* repStr);

