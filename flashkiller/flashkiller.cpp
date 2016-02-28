#include <windows.h>
#include <Tlhelp32.h>
#include <string>
#include <algorithm>

inline std::string lower(const char* str) {
	std::string res;
	auto size = strlen(str);
	res.resize(size);
	for (int i = 0; i < size;i++) {
		res[i] = tolower(str[i]);
	}
	return res;
}

void killProcessByName(const char *filename)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (lower(pEntry.szExeFile).find(filename) != std::string::npos)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, (DWORD)pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}


int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
	)
{
	killProcessByName("flashplayer");
	return 0;
}

