#include <Windows.h>
#include <GL/gl.h>
#include "WindowClass.h"
#include "ControllerGL.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    ModelGL modelGL;
    ViewGL viewGL;
    ControllerGL ctrlGL(&modelGL, &viewGL);

    WindowClass glWin(hInstance, L"WindowGL", NULL, &ctrlGL);
    glWin.setWindowStyle(WS_OVERLAPPEDWINDOW);
    glWin.setClassStyle(CS_OWNDC);
    glWin.setWidth(800);
    glWin.setHeight(600);

    if (!glWin.createWindow())
    {
        MessageBox(NULL, L"[Error] Failed to create GL window!", L"Error info", MB_OK);
        return -1;
    }
    ctrlGL.setHandle(glWin.getHandle());
    glWin.showWindow(nShowCmd);

    // Main message loop
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}