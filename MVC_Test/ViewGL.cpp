#include "ViewGL.h"

ViewGL::ViewGL() : m_hdc(0), m_hglrc(0)
{

}

ViewGL::~ViewGL()
{
}

bool ViewGL::createContext(HWND handle, int colorBits, int depthBits, int stencilBits)
{
    // retrieve a handle to a display device context
    m_hdc = ::GetDC(handle);

    // set pixel format
    if (!setPixelFormat(m_hdc, colorBits, depthBits, stencilBits))
    {
        ::MessageBox(0, L"Cannot set a suitable pixel format.", L"Error", MB_ICONEXCLAMATION | MB_OK);
        ::ReleaseDC(handle, m_hdc);                     // remove device context
        return false;
    }

    // Create and enable the OpenGL rendering context (RC)
    m_hglrc = ::wglCreateContext(m_hdc);
    

    //::ReleaseDC(handle, m_hdc);
    return true;

}

void ViewGL::closeContext(HWND handle)
{
    if (!m_hdc || !m_hglrc)
        return;

    // delete DC and RC
    ::wglMakeCurrent(0, 0);
    ::wglDeleteContext(m_hglrc);
    ::ReleaseDC(handle, m_hdc);

    m_hdc = 0;
    m_hglrc = 0;
}

void ViewGL::swapBuffers()
{
    ::SwapBuffers(m_hdc);
}

bool ViewGL::setPixelFormat(HDC hdc, int colorBits, int depthBits, int stencilBits)
{
    // Set the pixel format
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = colorBits;
    pfd.cDepthBits = depthBits;
    pfd.cStencilBits = stencilBits;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ::ChoosePixelFormat(hdc, &pfd);
    if (!::SetPixelFormat(hdc, pixelFormat, &pfd))
        return false;

    return true;
}
