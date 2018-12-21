#include <stdio.h>
#include <windows.h>

/*
    gcc shellcode.c -O2 -o shellcode.exe
*/
#define fail() while(1)
#define NFUNC 8


struct entry_code_data {
    char dllpath[0x400];
    char dllentry[0x200];
    
    
    char *k32base;
    union {
        void *k32fp[3];
        struct {
            HINSTANCE (WINAPI *my_LoadLibraryA)(LPCSTR lpLibFileName);
            HMODULE (WINAPI *my_GetModuleHandleA)(LPCSTR lpModuleName);
            FARPROC (WINAPI *my_GetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
        };
    };
};
void get_k32func(struct entry_code_data *data);
__declspec (dllexport) __declspec(noinline) DWORD WINAPI PleaseDumpMe(LPVOID lpParameter)
{
    unsigned codeloc;
    //__asm__ ("call 1f;1:pop %0" : "=r" (codeloc));
	__asm {
		CALL next
	next:
		POP EAX
		ADD EAX, 0xAABBCCDD // CHANGE THIS OFFSET VALUE AFTER COMPILE!
		MOV codeloc, EAX
	}
    struct entry_code_data *data = (void *)(codeloc);
    get_k32func(data);
    
    DWORD (WINAPI *entry)(LPVOID lpParameter) = (void *) data->my_GetProcAddress(data->my_LoadLibraryA(data->dllpath), data->dllentry);
    
    return entry(lpParameter);
}

__forceinline void get_k32func(struct entry_code_data *data)
{
    unsigned uk32[4];
    unsigned lk32;
    char *k32 = (char *)uk32;
    lk32 = 12 + 1;
    uk32[0] = 0x4E52454B;
    uk32[1] = 0x32334C45;
    uk32[2] = 0x4C4C442E;
    uk32[3] = 0x00000000;
    
    unsigned uk32fn[3][5];
    uk32fn[0][0] = 0x64616F4C;
    uk32fn[0][1] = 0x7262694C;
    uk32fn[0][2] = 0x41797261;
    uk32fn[0][3] = 0x00000000;
    uk32fn[0][4] = 0x00000000;
    uk32fn[1][0] = 0x4D746547;
    uk32fn[1][1] = 0x6C75646F;
    uk32fn[1][2] = 0x6E614865;
    uk32fn[1][3] = 0x41656C64;
    uk32fn[1][4] = 0x00000000;
    uk32fn[2][0] = 0x50746547;
    uk32fn[2][1] = 0x41636F72;
    uk32fn[2][2] = 0x65726464;
    uk32fn[2][3] = 0x00007373;
    uk32fn[2][4] = 0x00000000;

    char *peb;
    char *eat;
    unsigned nr_list;
    unsigned *list;
    unsigned i, j;

//    __asm__ ("movl %%fs:0x30, %0" : "=r" (peb));
	__asm {
		MOV EAX, DWORD PTR FS:[30H]
		MOV peb, EAX
	}
    peb = *(void **)(peb + 0x0c);
    peb = *(void **)(peb + 0x14);
    
    while (1) {
        wchar_t *str = *(void **)(peb + 0x28);
        if (!str) fail();
        
        //printf("%ws\n", str);
    
        for (i = 0; i < lk32; i++) {
            char ch = (char) str[i];
            if ('a' <= ch && ch <= 'z') ch = ch - 'a' + 'A';
            if (ch != k32[i]) break;
        }
        if (i >= lk32) break;
        
        peb = *(void **)(peb);
    }
    
    /* should equal to GetModuleHandle("kernel32.dll") */
    data->k32base = *(void **)(peb + 0x10);
    //printf("dllbase=%p %p\n", k32_base, GetModuleHandle("kernel32.dll"));
    
    eat = *(unsigned *)(*(unsigned *)(data->k32base + 0x3c) + data->k32base + 0x78) + data->k32base;
    //printf("EAT=%p\n", eat);
    
    nr_list = *(unsigned *)(eat + 0x18);
    list = (void *)(*(unsigned *)(eat + 0x20) + data->k32base);
    
    for (i = 0; i < nr_list; i++) {
        for (j = 0; j < 3; j++) {
            char *str = list[i] + data->k32base;
            char *fn = (char *)uk32fn[j];
            while (*str && *fn && *fn == *str) fn++, str++;
            if (*str == *fn) {
                data->k32fp[j] = *(int *)(*(int *)(eat + 0x1c) + data->k32base + (
                     *(unsigned short *)(*(int *)(eat + 0x24) + data->k32base + i * 2)
                   ) * 4) + data->k32base;
                break;
            }
        }
    }
}

int main()
{
    struct entry_code_data data;
    memset(&data, 0, sizeof(data));
	//__asm { int 3 }
    get_k32func(&data);
    
    int i;
    for (i = 0; i < 3; i++) {
        printf("%p\n", data.k32fp[i]);
    }

	//ThreadEntry("Hello");

    
    system("pause");
    return 0;
}
