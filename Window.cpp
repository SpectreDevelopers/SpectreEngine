#include <windows.h>
#include <tchar.h>

const TCHAR szClassName[] = _T("Spectre Engine");

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        {
            HMENU hMenubar = CreateMenu();
            HMENU hFileMenu = CreateMenu();
            HMENU hEditMenu = CreateMenu();
            HMENU hHelpMenu = CreateMenu();

            AppendMenu(hFileMenu, MF_STRING, 1, _T("Exit"));
            AppendMenu(hEditMenu, MF_STRING, 2, _T("Button"));
            AppendMenu(hHelpMenu, MF_STRING, 3, _T("About"));

            AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFileMenu, _T("File"));
            AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hEditMenu, _T("Edit"));
            AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hHelpMenu, _T("Help"));

            SetMenu(hwnd, hMenubar);
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        case 2:
            MessageBox(hwnd, _T("Clicked"), _T("Edit"), MB_OK);
            break;
        case 3:
            MessageBox(hwnd, _T("This is the Spectre Engine made by The Timetaker and Visualar (https://github.com/SpectreDevelopers)."), _T("About"), MB_OK);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = szClassName;

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, _T("Window Registration Failed!"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0,
        szClassName,
        _T("Engine"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL) {
        MessageBox(NULL, _T("Window Creation Failed!"), _T("Error"), MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
