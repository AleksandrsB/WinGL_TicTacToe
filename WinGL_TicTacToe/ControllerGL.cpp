#include "ControllerGL.h"


void ControllerGL::glRunThread()
{
    // set the current RC in this thread
    ::wglMakeCurrent(m_viewGL->getDC(), m_viewGL->getRC());

    // initialize OpenGL states
    m_modelGL->init();

    // cofigure projection matrix
    RECT rect;
    ::GetClientRect(m_winHandle, &rect);
    m_modelGL->setViewport(rect.right, rect.bottom);

    // rendering loop
    while (loopFlag)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // yield to other processes or threads

        if (resizeFlag)
        {
            m_modelGL->setViewport(clientWidth, clientHeight);
            resizeFlag = false;
        }

        m_modelGL->draw();
        m_viewGL->swapBuffers();
    }

    // close OpenGL Rendering context
    m_viewGL->closeContext(m_winHandle);
    ::wglMakeCurrent(0, 0);             // unset RC
}

ControllerGL::ControllerGL(ModelGL* model, ViewGL* view) : m_modelGL(model), m_viewGL(view), clientWidth(0), clientHeight(0), loopFlag(false), resizeFlag(false)
{

}

LRESULT ControllerGL::create()
{
    // create a OpenGL rendering context
    if (!m_viewGL->createContext(m_winHandle, 32, 24, 8))
    {
        //Win::log(L"[ERROR] Failed to create OpenGL rendering context from ControllerGL::create().");
        return -1;
    }

    // create a thread for OpenGL rendering
    glThread = std::thread(&ControllerGL::glRunThread, this);
    loopFlag = true;
    return 0;
}

LRESULT ControllerGL::close()
{
    // wait for rendering thread is terminated
    loopFlag = false;
    glThread.join();

    ::DestroyWindow(m_winHandle);
    return 0;
}

LRESULT ControllerGL::destroy()
{
    ::PostQuitMessage(0);       // exit the message loop
    return 0;
}

LRESULT ControllerGL::paint()
{
    return 0;
}

LRESULT ControllerGL::size(int width, int height, WPARAM type)
{
    resizeFlag = true;
    clientWidth = width;
    clientHeight = height;
    return 0;
}

LRESULT ControllerGL::lButtonDown(WPARAM state, int x, int y)
{
    m_modelGL->setMousePosition(x, y);

    if (state == MK_LBUTTON)
    {
        m_modelGL->setMouseLeft(true);
    }

    return 0;
}

LRESULT ControllerGL::lButtonUp(WPARAM state, int x, int y) // game move
{
    m_modelGL->setMousePosition(x, y);
    m_modelGL->setMouseLeft(false);

    if (m_modelGL->makeMove(m_modelGL->hoverCellX, m_modelGL->hoverCellY, m_modelGL->currentPlayer))
    {
        int winner = m_modelGL->checkWinner();
        if (winner != 0) {
            // Handle win or draw
            MessageBox(m_winHandle, (winner == 3) ? L"Draw!" : (winner == 1 ? L"Player 1 Wins!" : L"Player 2 Wins!"), L"Game Over", MB_OK);
            m_modelGL->resetGame();
        }
    }

    return 0;
}

LRESULT ControllerGL::rButtonDown(WPARAM state, int x, int y)
{
    m_modelGL->setMousePosition(x, y);

    if (state == MK_RBUTTON)
    {
        m_modelGL->setMouseRight(true);
    }

    return 0;
}

LRESULT ControllerGL::rButtonUp(WPARAM state, int x, int y)
{
    m_modelGL->setMousePosition(x, y);
    m_modelGL->setMouseRight(false);

    return 0;
}

LRESULT ControllerGL::mouseMove(WPARAM state, int x, int y)
{
    m_modelGL->setMousePosition(x, y);
    return 0;
}

LRESULT ControllerGL::keyDown(int key, LPARAM lParam)
{
    if (key == VK_ESCAPE)
    {
        ::PostMessage(m_winHandle, WM_CLOSE, 0, 0);
    }

    return 0;
}
