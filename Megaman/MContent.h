#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
using namespace std;
class MContent
{
private:

	LPDIRECT3DDEVICE9 d3ddv;
public:
	LPDIRECT3DTEXTURE9 LoadTexture(string path);
	LPDIRECT3DSURFACE9 LoadSurface(string path);
	MContent(LPDIRECT3DDEVICE9);
	~MContent(void);
};
