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
	HRESULT hr= DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&di8, NULL );
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

	did8->Poll();
	HRESULT hr = this->did8->GetDeviceState(sizeof(this->keyState),(LPVOID)&this->keyState);
	if(FAILED(hr))
	{
		while (this->did8->Acquire() == DIERR_INPUTLOST);				
	}

	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	did8->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), KeyEvents, &dwElements, 0 );

	// Scan through all data, check if the key is pressed or released
	for( DWORD i = 0; i < dwElements; i++ ) 
	{
		int KeyCode = KeyEvents[i].dwOfs;
		int KeyState = KeyEvents[i].dwData;
		if ( (KeyState & 0x80) > 0)
			_KeyDown = KeyCode; 
		else 
			_KeyUP = KeyCode;
	}
}

int MKeyboard::IsKeyDown(int Key)
{
	return keyState[Key] && 0x80;
}

int MKeyboard::GetKeyDown()
{

	int tam = _KeyDown;
	_KeyDown = 0;
	return tam;

}

int MKeyboard::GetKeyUp()
{
	int tam = _KeyUP;
	_KeyUP = 0;
	return tam;
}

MKeyboard::~MKeyboard(void)
{
	di8->Release();
	did8->Release();

}
