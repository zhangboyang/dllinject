#include <stdio.h>
#include <windows.h>

int main()
{
	while (1) {
		printf("My PID = %d, Running ...\n", GetProcessId(GetCurrentProcess()));
		Sleep(1000);
	}
}