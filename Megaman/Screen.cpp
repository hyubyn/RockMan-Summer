#include "Screen.h"


CScreen::CScreen(void)
{
	_isFinished = false;
	_camera = new Camera();
	_nextScreen = NULL;
}


CScreen::~CScreen(void)
{
	_isFinished = true;
	_camera->~Camera();
	_nextScreen->~CScreen();
}

bool CScreen::CheckFinished()
{
	return _isFinished;
}

CScreen* CScreen::GetNextScreen()
{
	return _nextScreen;
}
