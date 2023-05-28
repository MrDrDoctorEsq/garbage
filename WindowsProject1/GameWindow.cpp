#include "GameWindow.h"
#include "WindowsProject1.h"

LRESULT CALLBACK GameWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        CREATESTRUCT* pParams = (CREATESTRUCT*)lParam;
        if (pParams->lpCreateParams == nullptr)
        {
            throw;
        }
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pParams->lpCreateParams);
        break;
    }
    GameWindow* pWnd = (GameWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (pWnd == nullptr)
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
        return pWnd->InternalWndProc(message, wParam, lParam);
}
INT_PTR CALLBACK GameWindow::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
        UNREFERENCED_PARAMETER(lParam);
        switch (message)
        {
        case WM_INITDIALOG:
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            break;
        }
        return (INT_PTR)FALSE;
}
GameWindow::GameWindow(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow)
    : hInst(hInstance)
    , hWnd(0)
    , lpCmdLine(lpCmdLine)
    , nCmdShow(nCmdShow)
    , ExitCode(0)

{
    hInst = hInstance;
    szTitle[0] = 0;
    szWindowClass[0] = 0;
}
GameWindow::~GameWindow()
{

}
bool GameWindow::Initialize(const wchar_t* classId, const wchar_t* title)
{
    wcscpy_s(szTitle, title);
    wcscpy_s(szWindowClass, classId);
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInst;
    wcex.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    RegisterClassExW(&wcex);

    hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInst, this);

    if (!hWnd)
    {
        return false;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return true;
}
bool GameWindow::Run()
{
    MSG msg;
    if (!GetMessage(&msg, nullptr, 0, 0))
    {
        ExitCode = ((int)msg.wParam);
        return false;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    return true;
}
LRESULT CALLBACK GameWindow::InternalWndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_ERASEBKGND:
        return 0;
    case WM_PAINT:
        DrawWindow();
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
        OnKeyDown(wParam);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void GameWindow::OnPaint(HDC hDC)
{

}
void GameWindow::DrawWindow()
{

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rtClient;
        GetClientRect(hWnd, &rtClient);
        int xSize = rtClient.right - rtClient.left;
        int ySize = rtClient.bottom - rtClient.top;
        HDC hMemoryDC = CreateCompatibleDC(hdc);
        HBITMAP hScreenBitmap = CreateCompatibleBitmap(GetDC(NULL), xSize, ySize);
        SelectObject(hMemoryDC, hScreenBitmap);
        OnPaint(hMemoryDC);
        BitBlt(hdc, 0, 0, xSize, ySize, hMemoryDC, 0, 0, SRCCOPY);
        EndPaint(hWnd, &ps);
        DeleteObject(hScreenBitmap);
        DeleteDC(hMemoryDC);
}
void GameWindow::OnKeyDown(int vkCode)
{

}