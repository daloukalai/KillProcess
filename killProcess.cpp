#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

using namespace std;
void killNotepadProcess()
{
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    int count = 0;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if ((lstrcmp(entry.szExeFile, L"notepad.exe") == 0))
            {  
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                DWORD dwExitCode = 9999;
                if(GetExitCodeProcess(hProcess, &dwExitCode))
                {
                    if(TerminateProcess(hProcess, dwExitCode))
                        count++;
                }
                CloseHandle(hProcess);
            }
        }
    }
    CloseHandle(snapshot);

    if (count >= 1)
        cout << count << " notepad.exe processes are terminated successfully." << endl;
}

int main()
{
    killNotepadProcess();
    return 0;
}
