#include "framework.h"
#include "Tetris.h"
#include <time.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{

    srand(time(0));

    Tetris game(hInstance, lpCmdLine, nCmdShow);

    if (!game.Initialize(L"garbage", L"AAAAAAAAAAAAA"))
    {
        return false;
    }
    __int64 time;
    __int64 prev_time;
    __int64 frequency;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    QueryPerformanceCounter((LARGE_INTEGER*)&prev_time);
    while (game.Run())
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&time);
        float dt = double(time - prev_time) / frequency;
        game.Update(dt);
        prev_time = time;
    }
    return game.GetExitCode();
}