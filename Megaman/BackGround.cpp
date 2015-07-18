#include "BackGround.h"


BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

void BackGround::Init(MContent* content)
{
	this->img = content->LoadTexture("Resources\\Terrain\\background.png");
	width = 583;
	height = 255;
	this->position = D3DXVECTOR2(-5, -5);
}

void BackGround::Update(float gameTime, MKeyboard* key, Camera* Cam)
{

}
void BackGround::Render(MGraphic* graphic, Camera* cam)
{
	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);
	graphic->DrawTexture(this->img, position, center, D3DCOLOR_XRGB(255, 255, 255), cam);
}