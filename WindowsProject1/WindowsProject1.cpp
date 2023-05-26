// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Tetris.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    Tetris game(hInstance, lpCmdLine, nCmdShow);
    if (!game.Initialize(L"garbage", L"AAAAAAAAAAAAA"))
    {
        return false;
    }
    while (game.Run())
    {

    }
    return game.GetExitCode();
}