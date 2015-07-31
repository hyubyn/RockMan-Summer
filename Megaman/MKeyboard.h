#pragma once
#include <dinput.h>
#include "Global.h"
class MKeyboard
{

	
		HWND hWnd; 
		IDirectInput8 *di8; 
		IDirectInputDevice8 *did8;
		char keyState[256]; 
		DIMOUSESTATE MouseState;
		DIDEVICEOBJECTDATA KeyEvents[ KEYBOARD_BUFFER_SIZE ]; 
		int _KeyUP,_KeyDown;
		int _PreState[2];//1 down,2 up
		POINT position; 
		HINSTANCE hInstance;



public:
	char GetKeyState(int key) { return keyState[key]; }
	bool Init();
	MKeyboard(HINSTANCE hIns,HWND hwnd);	
	void GetState();
	int IsKeyDown(int Key);
	int GetKeyDown();
	int GetKeyUp();
	bool IsPreKeyDown(int Key);	
	~MKeyboard(void);
};

