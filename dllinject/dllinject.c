#define _CRT_SECURE_NO_WARNINGS

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
	char *rpage;
	char buf[4096];
	memset(buf, 0, sizeof(buf));
	
	// PUT DUMPED SHELL CODE HERE
	// DO NOT FORGET TO MODIFY THE OFFSET VALUE
	char code[]="\x55\x8B\xEC\x81\xEC\x88\x00\x00\x00\xE8\x00\x00\x00\x00\x58\x05\xF2\x07\x00\x00\x89\x45\xD4\x8B\x45\xD4\x89\x45\xF8\x8D\x4D\xB4\x89\x4D\xD0\xC7\x45\xD8\x0D\x00\x00\x00\xBA\x04\x00\x00\x00\x6B\xC2\x00\xC7\x44\x05\xB4\x4B\x45\x52\x4E\xB9\x04\x00\x00\x00\xC1\xE1\x00\xC7\x44\x0D\xB4\x45\x4C\x33\x32\xBA\x04\x00\x00\x00\xD1\xE2\xC7\x44\x15\xB4\x2E\x44\x4C\x4C\xB8\x04\x00\x00\x00\x6B\xC8\x03\xC7\x44\x0D\xB4\x00\x00\x00\x00\xBA\x14\x00\x00\x00\x6B\xC2\x00\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\x6B\xC2\x00\xC7\x04\x01\x4C\x6F\x61\x64\xB9\x14\x00\x00\x00\x6B\xD1\x00\x8D\x84\x15\x78\xFF\xFF\xFF\xB9\x04\x00\x00\x00\xC1\xE1\x00\xC7\x04\x08\x4C\x69\x62\x72\xBA\x14\x00\x00\x00\x6B\xC2\x00\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\xD1\xE2\xC7\x04\x11\x61\x72\x79\x41\xB8\x14\x00\x00\x00\x6B\xC8\x00\x8D\x94\x0D\x78\xFF\xFF\xFF\xB8\x04\x00\x00\x00\x6B\xC8\x03\xC7\x04\x0A\x00\x00\x00\x00\xBA\x14\x00\x00\x00\x6B\xC2\x00\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\xC1\xE2\x02\xC7\x04\x11\x00\x00\x00\x00\xB8\x14\x00\x00\x00\xC1\xE0\x00\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\x6B\xC2\x00\xC7\x04\x01\x47\x65\x74\x4D\xB9\x14\x00\x00\x00\xC1\xE1\x00\x8D\x94\x0D\x78\xFF\xFF\xFF\xB8\x04\x00\x00\x00\xC1\xE0\x00\xC7\x04\x02\x6F\x64\x75\x6C\xB9\x14\x00\x00\x00\xC1\xE1\x00\x8D\x94\x0D\x78\xFF\xFF\xFF\xB8\x04\x00\x00\x00\xD1\xE0\xC7\x04\x02\x65\x48\x61\x6E\xB9\x14\x00\x00\x00\xC1\xE1\x00\x8D\x94\x0D\x78\xFF\xFF\xFF\xB8\x04\x00\x00\x00\x6B\xC8\x03\xC7\x04\x0A\x64\x6C\x65\x41\xBA\x14\x00\x00\x00\xC1\xE2\x00\x8D\x84\x15\x78\xFF\xFF\xFF\xB9\x04\x00\x00\x00\xC1\xE1\x02\xC7\x04\x08\x00\x00\x00\x00\xBA\x14\x00\x00\x00\xD1\xE2\x8D\x84\x15\x78\xFF\xFF\xFF\xB9\x04\x00\x00\x00\x6B\xD1\x00\xC7\x04\x10\x47\x65\x74\x50\xB8\x14\x00\x00\x00\xD1\xE0\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\xC1\xE2\x00\xC7\x04\x11\x72\x6F\x63\x41\xB8\x14\x00\x00\x00\xD1\xE0\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\xD1\xE2\xC7\x04\x11\x64\x64\x72\x65\xB8\x14\x00\x00\x00\xD1\xE0\x8D\x8C\x05\x78\xFF\xFF\xFF\xBA\x04\x00\x00\x00\x6B\xC2\x03\xC7\x04\x01\x73\x73\x00\x00\xB9\x14\x00\x00\x00\xD1\xE1\x8D\x94\x0D\x78\xFF\xFF\xFF\xB8\x04\x00\x00\x00\xC1\xE0\x02\xC7\x04\x02\x00\x00\x00\x00\x64\xA1\x30\x00\x00\x00\x89\x45\xF0\x8B\x4D\xF0\x8B\x51\x0C\x89\x55\xF0\x8B\x45\xF0\x8B\x48\x14\x89\x4D\xF0\xBA\x01\x00\x00\x00\x85\xD2\x0F\x84\x88\x00\x00\x00\x8B\x45\xF0\x8B\x48\x28\x89\x4D\xDC\x83\x7D\xDC\x00\x75\x0B\xBA\x01\x00\x00\x00\x85\xD2\x74\x02\xEB\xF5\xC7\x45\xF4\x00\x00\x00\x00\xEB\x09\x8B\x45\xF4\x83\xC0\x01\x89\x45\xF4\x8B\x4D\xF4\x3B\x4D\xD8\x73\x3D\x8B\x55\xF4\x8B\x45\xDC\x8A\x0C\x50\x88\x4D\xFF\x0F\xBE\x55\xFF\x83\xFA\x61\x7C\x13\x0F\xBE\x45\xFF\x83\xF8\x7A\x7F\x0A\x0F\xBE\x4D\xFF\x83\xE9\x20\x88\x4D\xFF\x0F\xBE\x55\xFF\x8B\x45\xD0\x03\x45\xF4\x0F\xBE\x08\x3B\xD1\x74\x02\xEB\x02\xEB\xB2\x8B\x55\xF4\x3B\x55\xD8\x72\x02\xEB\x0D\x8B\x45\xF0\x8B\x08\x89\x4D\xF0\xE9\x6B\xFF\xFF\xFF\x8B\x55\xF8\x8B\x45\xF0\x8B\x48\x10\x89\x8A\x00\x06\x00\x00\x8B\x55\xF8\x8B\x82\x00\x06\x00\x00\x8B\x4D\xF8\x8B\x91\x00\x06\x00\x00\x8B\x40\x3C\x8B\x4D\xF8\x8B\x89\x00\x06\x00\x00\x03\x4C\x02\x78\x89\x4D\xE0\x8B\x55\xE0\x8B\x42\x18\x89\x45\xCC\x8B\x4D\xF8\x8B\x91\x00\x06\x00\x00\x8B\x45\xE0\x03\x50\x20\x89\x55\xC8\xC7\x45\xF4\x00\x00\x00\x00\xEB\x09\x8B\x4D\xF4\x83\xC1\x01\x89\x4D\xF4\x8B\x55\xF4\x3B\x55\xCC\x0F\x83\xD1\x00\x00\x00\xC7\x45\xE4\x00\x00\x00\x00\xEB\x09\x8B\x45\xE4\x83\xC0\x01\x89\x45\xE4\x83\x7D\xE4\x03\x0F\x83\xB0\x00\x00\x00\x8B\x4D\xF8\x8B\x91\x00\x06\x00\x00\x8B\x45\xF4\x8B\x4D\xC8\x03\x14\x81\x89\x55\xEC\x6B\x55\xE4\x14\x8D\x84\x15\x78\xFF\xFF\xFF\x89\x45\xE8\x8B\x4D\xEC\x0F\xBE\x11\x85\xD2\x74\x2E\x8B\x45\xE8\x0F\xBE\x08\x85\xC9\x74\x24\x8B\x55\xE8\x0F\xBE\x02\x8B\x4D\xEC\x0F\xBE\x11\x3B\xC2\x75\x14\x8B\x45\xE8\x83\xC0\x01\x89\x45\xE8\x8B\x4D\xEC\x83\xC1\x01\x89\x4D\xEC\xEB\xC8\x8B\x55\xEC\x0F\xBE\x02\x8B\x4D\xE8\x0F\xBE\x11\x3B\xC2\x75\x40\x8B\x45\xF8\x8B\x88\x00\x06\x00\x00\x8B\x55\xE0\x03\x4A\x1C\x8B\x45\xF8\x8B\x90\x00\x06\x00\x00\x8B\x45\xE0\x03\x50\x24\x8B\x45\xF4\x0F\xB7\x14\x42\x8B\x45\xF8\x8B\x80\x00\x06\x00\x00\x03\x04\x91\x8B\x4D\xE4\x8B\x55\xF8\x89\x84\x8A\x04\x06\x00\x00\xEB\x05\xE9\x3D\xFF\xFF\xFF\xE9\x1A\xFF\xFF\xFF\x8B\x45\xF8\x05\x00\x04\x00\x00\x50\x8B\x4D\xF8\x51\x8B\x55\xF8\x8B\x82\x04\x06\x00\x00\xFF\xD0\x50\x8B\x4D\xF8\x8B\x91\x0C\x06\x00\x00\xFF\xD2\x89\x45\xC4\x8B\x45\x08\x50\xFF\x55\xC4\x8B\xE5\x5D\xC2\x04\x00";

	if (argc < 3 || sscanf(argv[1], "%d", &pid) < 0) {
		printf("usage: %s PID DLLNAME\n", argv[0]);
		return 1;
	}
	LPSTR dllname = argv[2];
	SIZE_T size = sizeof(buf);

	printf("inject %s to process %d ...\n", dllname, pid); 

	phandle = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, pid);
	printf("process handle = %p\n", phandle);
	if (phandle == NULL) {
		printf("OpenProcess failed!\n");
		return 1;
	}
    
	
	strcpy(buf+0x800, dllname);
	strcpy(buf+0x800+0x400, "_InjecteeThreadProc@4");
	memcpy(buf, code, sizeof(code));
	
	
	rpage = VirtualAllocEx(phandle, NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	printf("alloc remote memory = %p\n", rpage);
	if (rpage == NULL) {
		printf("VirtualAllocEx failed!\n");
		return 1;
	}

	bret = WriteProcessMemory(phandle, rpage, buf, size, NULL);
	printf("WriteProcessMemory returns %d\n", (int) bret);
	if (bret == FALSE) {
		printf("WriteProcessMemory failed!\n");
		return 1;
	}



	thandle = CreateRemoteThread(phandle, NULL, 0, (LPTHREAD_START_ROUTINE) rpage, rpage, 0, NULL);
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
		printf("remote thread returned %d\n", texitcode);

	printf("free remote memory ...\n");
	VirtualFreeEx(phandle, rpage, 0, MEM_RELEASE);

	printf("free handle ...\n");
	CloseHandle(thandle);
	CloseHandle(phandle);

	return 0;
}
