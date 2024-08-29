#include "Controller.h"

Controller::Controller() : m_winHandle(0)
{
}

Controller::~Controller()
{
	::DestroyWindow(m_winHandle);
}

LRESULT Controller::close()
{
	::DestroyWindow(m_winHandle);
	return 0;
}

