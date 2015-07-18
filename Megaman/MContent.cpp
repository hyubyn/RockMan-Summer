#include "MContent.h"


MContent::MContent(LPDIRECT3DDEVICE9 device)
{
	this->d3ddv = device;
}

LPDIRECT3DTEXTURE9 MContent::LoadTexture(string path)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	ZeroMemory(&info,sizeof(info));
	hr = D3DXGetImageInfoFromFile(path.c_str(),&info); 
	if(hr != D3D_OK)
		return NULL;
	hr = D3DXCreateTextureFromFileEx(this->d3ddv,
		path.c_str(),
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255,255,255),
		&info,
		NULL,&texture);

	if(hr != D3D_OK)
		return 0;
	return texture;
}

LPDIRECT3DSURFACE9 MContent::LoadSurface(string path)
{
	LPDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;
	HRESULT hr;
	ZeroMemory(&info,sizeof(info));
	hr = D3DXGetImageInfoFromFile(path.c_str(),&info); 
	if(hr != D3D_OK)
		return NULL;
	hr = this->d3ddv->CreateOffscreenPlainSurface(
		info.Width,
		info.Height,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		&surface,
		NULL);
	if(hr != D3D_OK)
		return 0;
	hr = D3DXLoadSurfaceFromFile(surface,NULL,NULL,path.c_str(),NULL,D3DX_DEFAULT,D3DCOLOR_XRGB(255,255,255),&info);
	if(hr != D3D_OK)
		return 0;
	return surface;
}

MContent::~MContent(void)
{

}
