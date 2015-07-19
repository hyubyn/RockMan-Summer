#include "MKeyboard.h"


MKeyboard::MKeyboard(HINSTANCE hIns,HWND hwnd)
{
	this->di8 = 0;
	this->did8 = 0;
	this->hInstance = hIns;
	this->hWnd = hwnd;
	//create 
}

bool MKeyboard::Init()
{
	HRESULT hr= DirectInput8Create(
		this->hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&this->di8,
		NULL);
	if(FAILED(hr))
		return false;
	hr = this->di8->CreateDevice(GUID_SysKeyboard,&this->did8,NULL);
	if(FAILED(hr))
		return false;
	hr = this->did8->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
		return false;
	hr = this->did8->SetCooperativeLevel(this->hWnd,DISCL_FOREGROUND| DISCL_NONEXCLUSIVE);
	if(FAILED(hr))
		return false;	
	

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size


	hr =this->did8->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(hr))
		return false;

	hr = this->did8->Acquire();
	if (FAILED(hr))
		return false;
	return true;
}
void MKeyboard::GetState()
{
	HRESULT hr = this->did8->GetDeviceState(sizeof(this->key_buffer),(LPVOID)&this->key_buffer);
	if(FAILED(hr))
	{
		while (this->did8->Acquire() == DIERR_INPUTLOST);				
	}
}

bool MKeyboard::IsKeyDown(int Key)
{
	return key_buffer[Key] && 0x80;
}

MKeyboard::~MKeyboard(void)
{
}
