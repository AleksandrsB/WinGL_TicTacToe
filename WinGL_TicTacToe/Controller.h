#pragma once
#include <Windows.h>

class Controller
{
protected:
	HWND m_winHandle; // winHandle to controller window

public:
	// ctor/dtor
	Controller();
	virtual ~Controller();

	HWND getHandle() { return m_winHandle; }; // get window handle
	void setHandle(HWND winHandle) { m_winHandle = winHandle; } // set window handle

	virtual LRESULT close();										// for WM_CLOSE
	virtual LRESULT create() = 0;									// for WM_CREATE
	virtual LRESULT paint() = 0;									// for WM_PAINT
	virtual LRESULT size(int w, int h, WPARAM wParam) = 0;			// for WM_SIZE: width, height, type(SIZE_MAXIMIZED...)
	virtual LRESULT lButtonDown(WPARAM state, int x, int y) = 0;    // for WM_LBUTTONDOWN: state, x, y
	virtual LRESULT lButtonUp(WPARAM state, int x, int y) = 0;      // for WM_LBUTTONUP: state, x, y
	virtual LRESULT rButtonDown(WPARAM wParam, int x, int y) = 0;   // for WM_RBUTTONDOWN: state, x, y
	virtual LRESULT rButtonUp(WPARAM wParam, int x, int y) = 0;     // for WM_RBUTTONUP: state, x, y
	virtual LRESULT mouseMove(WPARAM state, int x, int y) = 0;      // for WM_MOUSEMOVE: state, x, y

	virtual LRESULT keyDown(int key, LPARAM lParam)=0;				// for WM_KEYDOWN: keyCode, detailInfo
};

