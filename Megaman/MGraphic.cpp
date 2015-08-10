#include "MGraphic.h"


MGraphic* MGraphic::_pInstance = NULL;
MGraphic::MGraphic(HWND hwnd,int W,int H)
{
	this->_pInstance = NULL;
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

		
	// Khởi tạo font handler
	hr = D3DXCreateFont(this->d3ddev, FONT_SIZE, 0, FW_NORMAL, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Megaman 2", &d3dxSpriteFont);
	if (hr != D3D_OK)
		return false;
	return true;
	
}

MGraphic::~MGraphic(void)
{
}

void MGraphic::GetCam(Camera* cam)
{
	this->_cam = cam;
}

void MGraphic::SetDevice(LPDIRECT3DDEVICE9 d3ddev)
{
	this->d3ddev = d3ddev;
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

	D3DXVECTOR3 pos = cam->GetPointTransform(postion.x, postion.y);
	this->d3dxSprite->Draw(texture, &source, &center, &D3DXVECTOR3(pos.x, pos.y, 0), color);
}
void MGraphic::DrawTextureFlipx(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 postion, D3DXVECTOR3 center, RECT source, D3DCOLOR color, Camera* cam)
{
	D3DXVECTOR3 pos = cam->GetPointTransform(postion.x, postion.y);


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


void MGraphic::DrawString(string text, D3DXVECTOR2 position, D3DCOLOR color, bool isDrawAtCenter,  Camera* cam){

	RECT destRect;
	destRect.top = position.y;
	destRect.left = position.x;
	destRect.bottom = destRect.top + SCREEN_HEIGHT;
	destRect.right = destRect.left + SCREEN_WIDTH;

	DrawString(text, destRect, color, D3DXVECTOR2(1, 1), isDrawAtCenter, cam);
}

void MGraphic::Draw(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, bool isDrawAtCenter, D3DXVECTOR2 scale, SpriteEffects effects)
{
	//xét định tọa độ tâm của khung hình chữ nhật
	D3DXVECTOR3 center;

	if (isDrawAtCenter){
		center.x = (destinationRectangle.right - destinationRectangle.left) / 2;
		center.y = (destinationRectangle.bottom - destinationRectangle.top) / 2;
		center.z = 0;
	}
	else
	{
		center.x = destinationRectangle.left;
		center.y = destinationRectangle.top;
		center.z = 0;
	}

	// Nếu có set camera thì transform theo camera
	if (_cam != NULL){
		_cam->Transform(&position);
	}

	// đặt lại vị trí tương ứng giá trị scale
	D3DXVECTOR3 positionDraw;
	positionDraw.x = position.x / scale.x;
	positionDraw.y = position.y / scale.y;
	positionDraw.z = 0;

	// tạo hai ma trận lưu trữ hệ thống tọa độ cũ, mới 
	D3DXMATRIX oldMatrix, newMatrix;

	d3dxSprite->GetTransform(&oldMatrix);

	//đặt ma trận scale 
	D3DXMatrixIdentity(&newMatrix);
	newMatrix._11 = scale.x;
	newMatrix._22 = scale.y;

	switch (effects)
	{
	case SpriteEffects::FLIP_HORIZONTALLY:
		newMatrix._11 *= -1;
		positionDraw.x *= -1;
		break;
	case SpriteEffects::FLIP_VERTICALLY:
		newMatrix._22 *= -1;
		positionDraw.y *= -1;
		break;
	default:
		break;
	}

	d3dxSprite->SetTransform(&newMatrix);

	d3dxSprite->Draw(texture, &destinationRectangle, &center, &positionDraw, D3DCOLOR_XRGB(255, 255, 255));

	// đặt lại ma trận ban đầu
	d3dxSprite->SetTransform(&oldMatrix);
}
void MGraphic::Draw(LPDIRECT3DTEXTURE9 texture, RECT boundingRectangle, bool isDrawAtCenter, D3DXVECTOR2 scale, SpriteEffects effect){
	RECT destinationRectangle;
	destinationRectangle.left = 0;
	destinationRectangle.top = 0;
	destinationRectangle.right = boundingRectangle.right - boundingRectangle.left;
	destinationRectangle.bottom = boundingRectangle.bottom - boundingRectangle.top;

	D3DXVECTOR2 pos(boundingRectangle.left, boundingRectangle.top);

	Draw(texture, destinationRectangle, pos, isDrawAtCenter, scale, effect);
}
void MGraphic::Draw(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, bool isDrawAtCenter, SpriteEffects effect)
{
	Draw(texture, destinationRectangle, position, isDrawAtCenter, D3DXVECTOR2(1.0f, 1.0f), effect);
}
void MGraphic::Draw(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, D3DXVECTOR2 scale)
{
	Draw(texture, destinationRectangle, position, true, scale, SpriteEffects::NONE);
}

void MGraphic::DrawString(string text, RECT boundingRectangle, D3DCOLOR color, D3DXVECTOR2 scale, bool isDrawAtCenter, Camera* cam){

	// Nếu có camera thì chuyển vị theo camera
	if (_cam != NULL)
	{
		D3DXVECTOR2 drawPos(boundingRectangle.left, boundingRectangle.top);
		long width = boundingRectangle.right - boundingRectangle.left;
		long height = boundingRectangle.bottom - boundingRectangle.top;

		_cam->Transform(&drawPos);
		boundingRectangle.left = drawPos.x;
		boundingRectangle.top = drawPos.y;
		boundingRectangle.right = boundingRectangle.left + width;
		boundingRectangle.bottom = boundingRectangle.top + height;
	}

	// Chỉnh giá trị scale cho phù hợp
	D3DXMATRIX oldMatrix, newMatrix;
	this->d3dxSprite->GetTransform(&oldMatrix);

	// Tìm ra vị trí mới trong hệ tọa độ hệ thống mới
	boundingRectangle.top /= scale.y;
	boundingRectangle.left /= scale.x;

	// Cài đặt tọa độ hệ thống mới
	D3DXMatrixIdentity(&newMatrix);
	newMatrix._11 = scale.x;
	newMatrix._22 = scale.y;

	// Cài đặt hệ thống tọa độ mới
	this->d3dxSprite->SetTransform(&newMatrix);

	// Kiểm tra nếu chỉ định là vẽ tại tâm đoạn Text thì cần tính lại vị trí của khung hình chữ nhật
	if (isDrawAtCenter){
		boundingRectangle.top += FONT_SIZE / 2;
		boundingRectangle.left -= (FONT_SIZE*text.length()) / 2;
		boundingRectangle.bottom = boundingRectangle.top + SCREEN_HEIGHT;
		boundingRectangle.right = boundingRectangle.left + SCREEN_WIDTH;
	}

	// Vẽ bóng chữ
	RECT boundingRectangleShadow;
	boundingRectangleShadow.top = boundingRectangle.top + 1;
	boundingRectangleShadow.left = boundingRectangle.left + 1;
	boundingRectangleShadow.bottom = boundingRectangleShadow.top + SCREEN_HEIGHT;
	boundingRectangleShadow.right = boundingRectangleShadow.left + SCREEN_WIDTH;
	d3dxSpriteFont->DrawTextA(this->d3dxSprite, text.c_str(), text.length(), &boundingRectangleShadow, DT_LEFT, D3DCOLOR_XRGB(0, 0, 0));

	// Tiến hành vẽ chữ tại vị trí mới trong hệ thống tọa độ mới
	d3dxSpriteFont->DrawTextA(this->d3dxSprite, text.c_str(), text.length(), &boundingRectangle, DT_LEFT, color);
	
	// Reset lại ma trận hệ thống
	(this->d3dxSprite->SetTransform(&oldMatrix));
}

void MGraphic::DrawTile(LPDIRECT3DTEXTURE9 texture, RECT destinationRectangle, D3DXVECTOR2 position, bool isDrawAtCenter, D3DXVECTOR2 scale, Camera* _camera)
{
	//xét định tọa độ tâm của khung hình chữ nhật
	D3DXVECTOR3 center;

	if (isDrawAtCenter){
		center.x = (destinationRectangle.right - destinationRectangle.left) / 2;
		center.y = (destinationRectangle.bottom - destinationRectangle.top) / 2;
		center.z = 0;
	}
	else
	{
		center.x = destinationRectangle.left;
		center.y = destinationRectangle.top;
		center.z = 0;
	}

	// Nếu có set camera thì transform theo camera
	if (_camera != NULL){
		_camera->Transform(&position);
	}

	// đặt lại vị trí tương ứng giá trị scale
	D3DXVECTOR3 positionDraw;
	positionDraw.x = position.x / scale.x;
	positionDraw.y = position.y / scale.y;
	positionDraw.z = 0;

	// tạo hai ma trận lưu trữ hệ thống tọa độ cũ, mới 
	D3DXMATRIX oldMatrix, newMatrix;

	this->d3dxSprite->GetTransform(&oldMatrix);

	//đặt ma trận scale 
	D3DXMatrixIdentity(&newMatrix);
	newMatrix._11 = scale.x;
	newMatrix._22 = scale.y;

	this->d3dxSprite->SetTransform(&newMatrix);

	this->d3dxSprite->Draw(texture, &destinationRectangle, &center, &positionDraw, D3DCOLOR_XRGB(255,255,255));

	// đặt lại ma trận ban đầu
	this->d3dxSprite->SetTransform(&oldMatrix);
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

MGraphic* MGraphic::GetInstance()
{
	if(_pInstance == nullptr)
	{
			_pInstance = new MGraphic();
			_pInstance->InitD3D();
	}
	return _pInstance;
}
