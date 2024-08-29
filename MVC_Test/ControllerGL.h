#pragma once
#include "Controller.h"
#include "ViewGL.h"
#include "ModelGL.h"
#include <thread>

class ControllerGL : public Controller
{
private:
    ModelGL* m_modelGL;
    ViewGL* m_viewGL;

    volatile bool loopFlag;                     // rendering loop flag
    std::thread glThread;                       // opengl rendering thread
    bool resizeFlag;
    int clientWidth;                            // width of client area
    int clientHeight;                           // height of client area

private:
    void glRunThread();
public:
    ControllerGL(ModelGL* model, ViewGL* view);
    ~ControllerGL() {};              

    LRESULT create(); // create RC for OpenGL window and start new thread for rendering
    LRESULT close(); // close the RC and destroy OpenGL window
    LRESULT destroy();
    LRESULT paint();
    LRESULT size(int width, int height, WPARAM type);

    LRESULT lButtonDown(WPARAM state, int x, int y);
    LRESULT lButtonUp(WPARAM state, int x, int y);
    LRESULT rButtonDown(WPARAM state, int x, int y);
    LRESULT rButtonUp(WPARAM state, int x, int y);
    LRESULT mouseMove(WPARAM state, int x, int y);

    LRESULT keyDown(int key, LPARAM lParam);
};

