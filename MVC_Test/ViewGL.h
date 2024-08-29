#pragma once
#include <Windows.h>

class ViewGL
{
private:
    HDC m_hdc; // handle to device context
    HGLRC m_hglrc; // handle to OpenGL rendering context

public:
    ViewGL();                                
    ~ViewGL();

    bool createContext(HWND handle, int colorBits, int depthBits, int stencilBits);  // create OpenGL rendering context
    void closeContext(HWND handle);
    void swapBuffers();

    static bool setPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits);

    HDC getDC() const { return m_hdc; };
    HGLRC getRC() const { return m_hglrc; };
};

