#pragma once

#include <d3dx9.h>
#include <stdio.h>
#include <vector>
#include <dinput.h>
#include <stdarg.h>
#include <windows.h>
#include <cmath>

using namespace std;


#define GAME_NAME "Megaman"
#define SCREEN_WIDTH 300
#define SCREEN_HEIGHT 224
#define GAME_FPS 60
#define GRAVITY  -600.0f

#define KEYBOARD_BUFFER_SIZE 1024 
#define FRAMERATE 60

// ID đối tượng
#define ID_LAND 1

typedef LPDIRECT3DDEVICE9		Device;
typedef LPDIRECT3DSURFACE9		Surface;
typedef LPDIRECT3DTEXTURE9		Texture;
typedef LPD3DXSPRITE			Sprite;
typedef LPD3DXFONT				SpriteFont;
typedef LPDIRECT3D9				DirectX9;
typedef D3DXIMAGE_INFO			ImageInfo;
typedef D3DXVECTOR2				Vector2;
typedef D3DXVECTOR3				Vector3;
typedef D3DXVECTOR4				Vector4;
typedef LPDIRECTINPUT8			Input;
typedef LPDIRECTINPUTDEVICE8	InputDevice;
typedef DIDEVICEOBJECTDATA		DeviceObjectData;
typedef D3DXMATRIX				Matrix;
typedef D3DCOLOR				Color;
typedef RECT					Rect;

#define FONT_SIZE	8