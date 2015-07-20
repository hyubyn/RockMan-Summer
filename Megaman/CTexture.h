#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_
#include <d3dx9.h>
#include "Global.h"
#include "Camera.h"
#include "MGraphic.h"
#include "MContent.h"
class CTexture
{
protected:
	LPDIRECT3DTEXTURE9 _texture;// texture chính của hàm 
	int _height;// chiều cao của bức ảnh
	int _width;// chiều rộng của bức ảnh
	char* _pNamePath;// tên đường dẫn file
	void LoadImageFromFile(char* pNamePath, D3DCOLOR color);//load texture 
public:
	
	CTexture();
	CTexture(char* pNamePath, D3DCOLOR color);
	~CTexture();
	LPDIRECT3DTEXTURE9 GetTexture();
	int GetHeight();
	int GetWidth();
};
#endif