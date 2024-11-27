#include <Windows.h>
#include <iostream>
#include <fstream>

HHOOK MouseHook{};
HHOOK KeyboardHook{ };


LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
   
    if (nCode >= 0)
    {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
		POINT mousepos = pMouseStruct->pt;
        auto pHookData = (MSLLHOOKSTRUCT*)lParam;

    
        if ((pHookData->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
        {
			printf("Injected Input Detected\n");
            return 1;
        }
        if ((pHookData->flags & LLMHF_LOWER_IL_INJECTED) == LLMHF_LOWER_IL_INJECTED)
        {
			printf("Injected Input Detected\n");
            return 1;
        }
        
    }

    return CallNextHookEx(MouseHook, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) 
    {
        KBDLLHOOKSTRUCT* pKeyboardStruct = (KBDLLHOOKSTRUCT*)lParam;

        if ((pKeyboardStruct->flags & LLKHF_INJECTED) == LLKHF_INJECTED) 
        {
            printf("Injected Input Detected\n");
            return 1; 
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam); 
}

void InstallHooks()
{
    MouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);
	KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (MouseHook == NULL)
    {
        std::cerr << "Failed to install mouse hook!" << std::endl;
    }
    else
    {
        std::cout << "Mouse hook installed successfully!" << std::endl;
    }
}

void UninstallHooks()
{
   
    if (MouseHook != NULL)
    {
        UnhookWindowsHookEx(MouseHook);
        UnhookWindowsHookEx(KeyboardHook);
        std::cout << "Hook uninstalled!" << std::endl;
    }
}
