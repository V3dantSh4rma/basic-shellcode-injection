#include <Windows.h>
#include <stdio.h>
#include <processthreadsapi.h>

int main(){
    STARTUPINFO si = {0};
    PROCESS_INFORMATION pi = {0};
    if(!CreateProcessA("gui.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
        puts("[ERROR] Unable to create the process.");
        return EXIT_FAILURE;
    } else {
        DWORD pid = pi.dwProcessId;
        DWORD tid = pi.dwThreadId;
        HANDLE hProc = pi.hProcess;
        HANDLE hThread = pi.hThread;
        printf("(-) Process ID: %ld\n", pid);
        printf("(-) Thread ID: %ld\n", tid);
        printf("(-) Process Handler: 0x%x\n", hProc);
        printf("(-) Thread Handler: 0x%x\n", hThread);
        WaitForSingleObject(hProc, INFINITE);
        puts("(+) Process finished.");
        CloseHandle(hProc);
        CloseHandle(hThread);
        return EXIT_SUCCESS;
    }
}