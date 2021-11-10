#pragma once

#include <vector>
#include <Windows.h>
#include <string>

typedef struct
{
    DWORD pid;
    char srcStr[20];
    char repStr[20];

} loadLibraryInfo;

extern "C" __declspec(dllexport) void __cdecl ReplaceString(loadLibraryInfo* info);
