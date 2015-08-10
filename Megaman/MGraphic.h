#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Camera.h"
#include "CSingleton.h"
#include <string>
#include "Global.h"

using namespace std;

enum SpriteEffects{
	NONE = 0, // Không chỉ định xoay
	FLIP_HORIZONTALLY = 1, // Xoay 1 góc 180 quanh trục Y
	FLIP_VERTICALLY = 2  // Xoay 1 góc 180 quanh trục X
};

class MGraphic 
{
private :

	//doi tuong direct x
	LPDIRECT3D9 d3d;
	//thiet bi ve
	LPDIRECT3DDEVICE9 d3ddev;
	//Ve texture
	LPD3DXSPRITE d3dxSprite;
	LPD3DXFONT d3dxSpriteFont;
	//ve text

	//hwnd cua cua so ve
	HWND hWnd;
	int Width;
	int Height;
	Camera* _cam;
public:
	bool InitD3D();
	MGraphic(HWND,int,int);
	MGraphic(){}
	~MGraphic(void);
	void Begin();
	void End();
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, RECT source, D3DCOLOR color, Camera* cam);
	void DrawTextureFlipx(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, RECT source, D3DCOLOR color, Camera* cam);
	void DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, D3DCOLOR color, Camera* cam);
	
	void Draw(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, bool isDrawAtCenter, D3DXVECTOR2 scale = D3DXVECTOR2(1,1), SpriteEffects effects = SpriteEffects::NONE);
	void Draw(LPDIRECT3DTEXTURE9 texture, RECT boundingRectangle, bool isDrawAtCenter, D3DXVECTOR2 scale, SpriteEffects effect);
	void Draw(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, bool isDrawAtCenter, SpriteEffects effect);
	void Draw(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, D3DXVECTOR2 scale);

	
	void DrawTile(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, bool isDrawAtCenter, D3DXVECTOR2 scale, Camera* cam);
	void DrawString(string text, D3DXVECTOR2 position, D3DCOLOR color, bool isDrawAtCenter, Camera* cam);
	void DrawString(string text, RECT boundingRectangle, D3DCOLOR color , D3DXVECTOR2 scale, bool isDrawAtCenter, Camera* cam);
	void DrawString(char* str);
	void DrawSurface();
	void GetCam(Camera* cam);
	void SetDevice(LPDIRECT3DDEVICE9 d3ddev);
	LPDIRECT3DDEVICE9 GetDevice();	
	static MGraphic* GetInstance();
protected:
	static MGraphic*	_pInstance;
};

