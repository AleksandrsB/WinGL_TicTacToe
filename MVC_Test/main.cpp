#include <Windows.h>
#include <GL/gl.h>
#include "WindowClass.h"
#include "ControllerGL.h"

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitializeOpenGL(HWND hWnd);
void Render();

// Global variables
HDC hDC;
HGLRC hRC;



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

    // Initialize OpenGL
    //InitializeOpenGL(glWin.getHandle());

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

void InitializeOpenGL(HWND hWnd) {
    // Get the device context (DC)
    hDC = GetDC(hWnd);

    // Set the pixel format
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, pixelFormat, &pfd);

    // Create and enable the OpenGL rendering context (RC)
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    // Set up the OpenGL viewport
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void Render() {
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a rectangle
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glVertex2f(-0.5f, -0.5f);    // Bottom left
    glVertex2f(0.5f, -0.5f);     // Bottom right
    glVertex2f(0.5f, 0.5f);      // Top right
    glVertex2f(-0.5f, 0.5f);     // Top left
    glEnd();

    glFlush(); // Ensure everything is drawn
}