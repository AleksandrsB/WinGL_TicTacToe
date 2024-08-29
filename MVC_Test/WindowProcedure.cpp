#include "WindowProcedure.h"
#include "Controller.h"

LRESULT Procedure::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT returnValue = 0;

	// find controller associated with window handle
	static Controller* ctrl;
	ctrl = (Controller*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (msg == WM_NCCREATE)  // Non-Client Create
	{
		// WM_NCCREATE message is called before non-client parts(border,
		// titlebar, menu,etc) are created. This message comes with a pointer
		// to CREATESTRUCT in lParam. The lpCreateParams member of CREATESTRUCT
		// actually contains the value of lpPraram of CreateWindowEX().
		// First, retrieve the pointrer to the controller specified when
		// Win::Window is setup.
		ctrl = (Controller*)(((CREATESTRUCT*)lParam)->lpCreateParams);
		ctrl->setHandle(hWnd);

		// Second, store the pointer to the Controller into GWLP_USERDATA,
		// so, other messege can be routed to the associated Controller.
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)ctrl);

		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	// check NULL pointer, because GWLP_USERDATA is initially 0, and
	// we store a valid pointer value when WM_NCCREATE is called.
	if (!ctrl)
		return ::DefWindowProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_CREATE:
		returnValue = ctrl->create();
		break;
	case WM_CLOSE:
		returnValue = ctrl->close();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		returnValue = ctrl->size(LOWORD(lParam), HIWORD(lParam), (int)wParam);  // width, height, type
		break;
	case WM_PAINT:
		ctrl->paint();
		returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
		break;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		returnValue = ctrl->keyDown((int)wParam, lParam);                       // keyCode, keyDetail
		break;

	case WM_LBUTTONDOWN:
		returnValue = ctrl->lButtonDown(wParam, LOWORD(lParam), HIWORD(lParam)); // state, x, y
		break;

	case WM_LBUTTONUP:
		returnValue = ctrl->lButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
		break;

	case WM_RBUTTONDOWN:
		returnValue = ctrl->rButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));// state, x, y
		break;

	case WM_RBUTTONUP:
		returnValue = ctrl->rButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
		break;
	case WM_MOUSEMOVE:
		returnValue = ctrl->mouseMove(wParam, LOWORD(lParam), HIWORD(lParam));  // state, x, y
		break;
	default:
		return DefWindowProcW(hWnd, msg, wParam, lParam);
	}
}