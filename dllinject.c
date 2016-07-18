#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main(int argc, char *argv[])
{
	BOOL bret;
	DWORD pid;
	DWORD texitcode;
	HANDLE phandle, thandle;
	LPVOID rdllname;
	FARPROC loadlibrary;

	if (argc < 3 || sscanf(argv[1], "%d", &pid) < 0) {
		printf("usage: %s PID DLLNAME\n", argv[0]);
		return 1;
	}
	LPSTR dllname = argv[2];
	SIZE_T size = strlen(argv[2]) + 1;

	printf("inject %s to process %d ...\n", dllname, pid); 

	phandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
	printf("process handle = %p\n", phandle);
	if (phandle == NULL) {
		printf("OpenProcess failed!\n");
		return 1;
	}

	rdllname = VirtualAllocEx(phandle, NULL, size, MEM_COMMIT, PAGE_READWRITE);
	printf("alloc remote memory = %p\n", rdllname);
	if (rdllname == NULL) {
		printf("VirtualAllocEx failed!\n");
		return 1;
	}

	bret = WriteProcessMemory(phandle, rdllname, dllname, size, NULL);
	printf("WriteProcessMemory returns %d\n", (int) bret);
	if (bret == FALSE) {
		printf("WriteProcessMemory failed!\n");
		return 1;
	}

	loadlibrary = GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA");
	printf("address of LoadLibraryA = %p\n", loadlibrary);
	if (loadlibrary == NULL) {
		printf("GetProcAddress failed!\n");
		return 1;
	}

	thandle = CreateRemoteThread(phandle, NULL, 0, (LPTHREAD_START_ROUTINE) loadlibrary, rdllname, 0, NULL);
	printf("thread handle = %p\n", thandle);
	if (thandle == NULL) {
		printf("CreateRemoteThread failed!\n");
		return 1;
	}


	printf("wait for remote thread ...\n");
	WaitForSingleObject(thandle, INFINITE);

	bret = GetExitCodeThread(thandle, &texitcode);
	if (bret == FALSE)
		printf("GetExitCodeThread failed!\n");
	else
		printf("remote thread returns %p\n", texitcode);

	printf("free remote memory ...\n");
	VirtualFreeEx(phandle, rdllname, 0, MEM_RELEASE);

	printf("free handle ...\n");
	CloseHandle(thandle);
	CloseHandle(phandle);

	if (texitcode != 0)
		printf("finish!\n");
	else
		printf("finish, but it seems that an error has occurred.\n");

	return 0;
}
