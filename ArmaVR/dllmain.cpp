#include "dllmain.hpp"
#include "hooker.hpp"

#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

#include <iostream>
#include <fstream>

#include <io.h>
#include <stdio.h>
#include <fcntl.h>

using namespace std;
static const WORD MAX_CONSOLE_LINES = 500;

void CreateConsole()
{
    // Create console
    AllocConsole();
    HANDLE stdHandle;
    int hConsole;
    FILE* fp;
    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    hConsole = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
    fp = _fdopen(hConsole, "w");

    freopen_s(&fp, "CONOUT$", "w", stdout);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            CreateConsole();
            std::cout << "ArmaVR is attached" << std::endl;
        }
        break;
        case DLL_THREAD_ATTACH:
        break;
        case DLL_THREAD_DETACH:
        break;
        case DLL_PROCESS_DETACH:
        {
            std::cout << "Detaching ArmaVR..." << std::endl;
            hooker::release();
        }
        break;
    }
    return TRUE;
}
