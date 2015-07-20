#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "CSingleton.h"
using namespace std;
class MContent : public CSingleton<MContent>
{
private:

	LPDIRECT3DDEVICE9 d3ddv;
public:
	LPDIRECT3DTEXTURE9 LoadTexture(string path);
	LPDIRECT3DSURFACE9 LoadSurface(string path);
	LPDIRECT3DDEVICE9 getDevice();
	MContent(LPDIRECT3DDEVICE9);
	~MContent(void);
};
