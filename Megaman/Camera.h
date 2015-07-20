#pragma once
#include "d3dx9.h"
class Camera
{
	D3DXMATRIX _MatrixTransform;
	D3DXVECTOR2 _oldPos;
public:
	Camera();
	~Camera();
	D3DXVECTOR2 _pos;
	RECT getViewPort();
	int width;
	int height;
	void Update(D3DXVECTOR2 megamanPos);
	D3DXVECTOR3 GetPointTransform(int x, int y);
	void Transform(D3DXVECTOR2* position);
};

