#include "pch.h"
#include "stringReplace.h"


extern "C" __declspec(dllexport) void __cdecl ReplaceString(DWORD pid, const char* srcStr, const char* repStr)
{
	HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, pid);
	size_t len = strlen(srcStr);
	size_t repLength = strlen(repStr);

	if (hProcess)
	{
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);

		MEMORY_BASIC_INFORMATION memInfo;
		std::vector<char> chunk;
		char* p = 0;

		while (p < systemInfo.lpMaximumApplicationAddress)
		{
			if (VirtualQueryEx(hProcess, p, &memInfo, sizeof(memInfo)) == sizeof(memInfo))
			{
				if (memInfo.State == MEM_COMMIT && memInfo.AllocationProtect == PAGE_READWRITE)
				{
					p = (char*)memInfo.BaseAddress;
					chunk.resize(memInfo.RegionSize);
					SIZE_T bytes;
					try
					{
						if (ReadProcessMemory(hProcess, p, &chunk[0], memInfo.RegionSize, &bytes))
						{
							for (size_t i = 0; i < (bytes - len); i++)
							{

								if (memcmp(srcStr, &chunk[i], len) == 0)
								{
									char* ch = (char*)p + i;
									for (int j = 0; j < repLength; j++)
									{
										ch[j] = repStr[j];
									}

									ch[repLength] = 0;
								}
							}
						}
					}
					catch (std::bad_alloc& e)
					{

					}
				}
			}

			p += memInfo.RegionSize;
		}
	}
}