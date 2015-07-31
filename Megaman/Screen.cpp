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

bool CScreen::IsFinished(){
	return _isFinished;
}

void CScreen::GetGraphic(MGraphic *gra)
{
	this->_graphic = gra;
}

void CScreen::SetInput(MKeyboard* input)
{
	this->_input = input;
}


void CScreen::GetCam(Camera* cam)
{
	this->_camera = cam;
}

