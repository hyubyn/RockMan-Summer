#pragma once
#include "d3dx9.h"
class Camera
{
	D3DXMATRIX _MatrixTransform;
public:
	Camera();
	~Camera();
	D3DXVECTOR2 _pos;
	int width;
	int height;
	void Update(int x);
	D3DXVECTOR3 GetPointTransform(int x, int y);
};

