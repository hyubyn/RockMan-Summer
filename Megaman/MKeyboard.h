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
	DIDEVICEOBJECTDATA KeyEvents[KEYBOARD_BUFFER_SIZE];
	int _KeyUP, _KeyDown;
	int _PreState[2];//1 down,2 up
	POINT position;
	HINSTANCE hInstance;

	// Bộ đệm trạng thái của bàn phím DirectInput 
	BYTE  _preKeyStates[256];
	bool  _isActive;

public:
	char GetKeyState(int key) { return keyState[key]; }
	bool Init();
	MKeyboard(HINSTANCE hIns, HWND hwnd);
	void GetState();
	int IsKeyDown(int Key);
	int GetKeyDown();
	int GetKeyUp();
	bool IsPreKeyDown(int keyCode);

	int IsKeyDown_M(int keyCode);
	int IsKeyUp(int keyCode);

	int IsKeyPress(int keyCode);

	int IsKeyRelease(int keyCode);

	void SaveKeyStateHistory();
	void Update();
	void Active();
	void Deactive();

	MKeyboard(void);
	~MKeyboard(void);
};

