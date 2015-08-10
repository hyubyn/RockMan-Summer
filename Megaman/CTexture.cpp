#include "CTexture.h"

CTexture::CTexture()
{

}

CTexture::CTexture(char* pNamePath, D3DCOLOR color, LPDIRECT3DDEVICE9 device)
{
	this->_pNamePath = pNamePath;
	LoadImageFromFile(_pNamePath, color, device);
}

CTexture::CTexture(char* pNamePath, D3DCOLOR color)
{
	this->_pNamePath = pNamePath;
	LoadImageFromFile(_pNamePath, color);
}

CTexture::~CTexture()
{

}
void CTexture::LoadImageFromFile(char* pNamePath, D3DCOLOR color)
{
	HRESULT result;
	D3DXIMAGE_INFO info;

	// Lấy thông tin từ file ảnh
	result = D3DXGetImageInfoFromFile(pNamePath, &info);
	if (result != D3D_OK)
	{
		// hiển thị một thông báo lỗi 
		
		return;
	}

	_width = info.Width;
	_height = info.Height;

	// Lấy thiết bị 
	LPDIRECT3DDEVICE9 pd3ddev = MGraphic::GetInstance()->GetDevice();
	if (pd3ddev)
		result = D3DXCreateTextureFromFileEx( // Tạo texture từ file ảnh
		pd3ddev,
		pNamePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,// bộ nhớ chổ nào còn thì lưu texture tại đó
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&info,
		NULL,
		&_texture);
	if (result != D3D_OK)
	{
		return;
	}
	
}


void CTexture::LoadImageFromFile(char* pNamePath, D3DCOLOR color, LPDIRECT3DDEVICE9 pd3ddev)
{
	HRESULT result;
	D3DXIMAGE_INFO info;

	// Lấy thông tin từ file ảnh
	result = D3DXGetImageInfoFromFile(pNamePath, &info);
	if (result != D3D_OK)
	{
		// hiển thị một thông báo lỗi 

		return;
	}

	_width = info.Width;
	_height = info.Height;

	if (pd3ddev)
		result = D3DXCreateTextureFromFileEx( // Tạo texture từ file ảnh
		pd3ddev,
		pNamePath,
		info.Width,
		info.Height,
		1,
		D3DPOOL_DEFAULT,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,// bộ nhớ chổ nào còn thì lưu texture tại đó
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		color,
		&info,
		NULL,
		&_texture);
	if (result != D3D_OK)
	{
		return;
	}

}

LPDIRECT3DTEXTURE9 CTexture::GetTexture()
{
	return _texture;
}
int CTexture::GetHeight()
{
	return _height;
}
int CTexture::GetWidth()
{
	return _width;
}