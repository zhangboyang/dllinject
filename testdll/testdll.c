#include <windows.h>

__declspec (dllexport) DWORD WINAPI InjecteeThreadProc(LPVOID lpParameter)
{
	MessageBoxA(NULL, "Hello World!", "Injectee", MB_ICONINFORMATION | MB_TOPMOST);
    return 0;
}