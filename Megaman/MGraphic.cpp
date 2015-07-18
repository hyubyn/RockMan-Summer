#include "MGraphic.h"


MGraphic::MGraphic(HWND hwnd,int W,int H)
{
	this->hWnd = hwnd;
	this->Width = W;
	this->Height = H;
	this->d3d = NULL;
	this->d3ddev = NULL;
	this->d3dxSprite = NULL;	
}

bool MGraphic::InitD3D()
{
	//tao mot doi tuong Direct3D
	this->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!this->d3d)
		return false;
	//tao thiet bi ve
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = this->Width;
	d3dpp.BackBufferHeight = this->Height;
	d3dpp.hDeviceWindow = this->hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	HRESULT hr = this->d3d->CreateDevice(D3DADAPTER_DEFAULT,//chon thiet bi ve mac dinh
		D3DDEVTYPE_HAL,//su dung ho tro cua phan cung
		this->hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->d3ddev);
	if(FAILED(hr))
	{		
		return false;
	}
	hr = D3DXCreateSprite(this->d3ddev,&this->d3dxSprite);
	if(FAILED(hr))
		return false;	
	return true;
}

MGraphic::~MGraphic(void)
{
}

void MGraphic::Begin()
{
	//mặc định là màu trắng
	this->d3ddev->Clear(1,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255),1,NULL);
	this->d3ddev->BeginScene();
	this->d3dxSprite->Begin(D3DXSPRITE_ALPHABLEND);
}
void MGraphic::End()
{
	this->d3dxSprite->End();
	this->d3ddev->EndScene();
	this->d3ddev->Present(NULL,NULL,NULL,NULL);
}

void MGraphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, RECT source, D3DCOLOR color, Camera* cam)
{

	D3DXVECTOR3 pos = cam->GetPointTransform(postion.x + center.x, postion.y + center.y);
	this->d3dxSprite->Draw(texture, &source, &center, &D3DXVECTOR3(pos.x, pos.y, 0), color);
}
void MGraphic::DrawTextureFlipx(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, RECT source, D3DCOLOR color, Camera* cam)
{
	D3DXVECTOR3 pos = cam->GetPointTransform(postion.x + center.x, postion.y + center.y);


	D3DXMATRIX oldMt;
	this->d3dxSprite->GetTransform(&oldMt);
	D3DXMATRIX newMt;
	D3DXVECTOR2 center2 = D3DXVECTOR2(pos.x + center.x, pos.y + center.y);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center2, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;

	this->d3dxSprite->SetTransform(&finalMt);

	this->d3dxSprite->Draw(texture, &source, &center, &D3DXVECTOR3(pos.x + center.x*2, pos.y, 0), color);

	this->d3dxSprite->SetTransform(&oldMt);
}

void MGraphic::DrawTexture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, D3DCOLOR color, Camera* cam)
{

	D3DXVECTOR3 pos = cam->GetPointTransform(postion.x + center.x, postion.y + center.y);
	this->d3dxSprite->Draw(texture, NULL, &center, &D3DXVECTOR3(pos.x, pos.y, 0), color);
}
void MGraphic::DrawSurface()
{

}

LPDIRECT3DDEVICE9 MGraphic::GetDevice()
{
	return this->d3ddev;
}


void MGraphic::DrawString(char* str)
{
	
}