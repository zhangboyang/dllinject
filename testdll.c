#include <windows.h>
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved )  // reserved
{
    // Perform actions based on the reason for calling.
    switch( fdwReason ) 
    { 
        case DLL_PROCESS_ATTACH:
         // Initialize once for each new process.
         // Return FALSE to fail DLL load.
			MessageBoxA(NULL, "DLL_PROCESS_ATTACH!", "Hello!", 0);
            break;

        case DLL_THREAD_ATTACH:
         // Do thread-specific initialization.
			MessageBoxA(NULL, "DLL_THREAD_ATTACH!", "Hello!", 0);
            break;

        case DLL_THREAD_DETACH:
         // Do thread-specific cleanup.
			MessageBoxA(NULL, "DLL_THREAD_DETACH!", "Hello!", 0);
            break;

        case DLL_PROCESS_DETACH:
         // Perform any necessary cleanup.
			MessageBoxA(NULL, "DLL_PROCESS_DETACH!", "Hello!", 0);
            break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
