/*
* File: Main.cpp
*/

#include "main.h"

int APIENTRY WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ PSTR cmdline, _In_ int cmdshow)
{
    App.Run(hInst, cmdshow);
    DWORD dw = GetLastError();
   // _CrtDumpMemoryLeaks();
    return 0;
}