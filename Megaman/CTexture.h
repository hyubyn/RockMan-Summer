#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_
#include <d3dx9.h>
#include "Global.h"
#include "Camera.h"
#include "MGraphic.h"
class CTexture
{
protected:
	LPDIRECT3DTEXTURE9 _texture;// texture chính của hàm 
	int _height;// chiều cao của bức ảnh
	int _width;// chiều rộng của bức ảnh
	wchar_t* _pNamePath;// tên đường dẫn file
	void LoadImageFromFile(wchar_t* pNamePath, D3DCOLOR color);//load texture 
public:
	
	CTexture();
	CTexture(wchar_t* pNamePath, D3DCOLOR color);
	~CTexture();
	LPDIRECT3DTEXTURE9 GetTexture();
	int GetHeight();
	int GetWidth();
};
#endif