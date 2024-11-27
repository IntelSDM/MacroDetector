#include <Windows.h>
#include <iostream>
#include "Input.h"
#include <chrono>
#include <thread>
void SendMouseInputThread() 
{
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.mi.dx = 100;
    input.mi.dy = 100; 
    input.mi.dwFlags = MOUSEEVENTF_MOVE;

    while (true)
    {
        SendInput(1, &input, sizeof(INPUT));
        Sleep(10); 
    }
}
void main()
{
    MSG msg;
    InstallHooks();
    std::thread inputThread(SendMouseInputThread);
    inputThread.detach();
    while (true)
    {
       
       if (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                break;
        }
	
        Sleep(0);

    }
    UninstallHooks();

}

