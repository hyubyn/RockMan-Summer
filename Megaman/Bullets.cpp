#include "Bullets.h"


Bullets::Bullets(MContent* content)
{
	this->img = content->LoadTexture("Resources\\Megaman\\Bullet.png");
	width = 10;
	height = 6;
	this->speed = D3DXVECTOR2(250, 300);
	shot = false;
}
Bullets::~Bullets()
{
}

void Bullets::IsShot(D3DXVECTOR2 Pos, bool r)
{
	if (r)
	{
		position.x = Pos.x + 24;
		position.y = Pos.y + 10;
	}
	else
	{
		position.x = Pos.x - 8;
		position.y = Pos.y + 10;
	}
	right = r;
	shot = true;

}

void Bullets::Update(float gameTime, Camera* cam)
{
	if (position.x <= cam->_pos.x || position.x >= cam->_pos.x + SCREEN_WIDTH)
	{
		shot = false;
	}
	if (right == true)
	{
		position.x += speed.x*gameTime;
	}
	else
	{
		position.x -= speed.x*gameTime;
	}
}
void Bullets::Render(MGraphic* graphic, Camera* cam)
{
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);
	graphic->DrawTexture(this->img, position, center, rect, D3DCOLOR_XRGB(255, 255, 255), cam);
}