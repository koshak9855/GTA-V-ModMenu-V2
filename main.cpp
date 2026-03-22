#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>

DWORD FindTargetProcess(const std::string& processName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_stricmp(procEntry.szExeFile, processName.c_str())) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

int main() {
    SetConsoleTitleA("Vanguard Controller - Win64 Auditor");
    std::cout << "Vanguard External Suite Initialization..." << std::endl;

    std::string targetApp = "GTA5.exe";
    DWORD processId = FindTargetProcess(targetApp);

    if (processId != 0) {
        std::cout << "[INFO] Found target process context (PID: " << processId << ")" << std::endl;
        std::cout << "[INFO] Initiating external overlay and script bridge..." << std::endl;
        // In actual implementation, we'd hook Render() and RPM() here.
    } else {
        std::cerr << "[ERROR] Please launch " << targetApp << " before initializing Vanguard." << std::endl;
    }

    std::cout << "Core cycle active. Press END to detach and clean resources." << std::endl;
    while (!(GetAsyncKeyState(VK_END) & 0x8000)) {
        Sleep(100);
    }

    return 0;
}
