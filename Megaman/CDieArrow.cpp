#include "CDieArrow.h"

CDieArrow::CDieArrow() :CStaticObject()
{
	_texture = CTexture("Resources//Sprites//Others//dieaarrow.png", D3DCOLOR_XRGB(0, 232, 216));
	UpdateBox();
}

CDieArrow::~CDieArrow()
{

}

int CDieArrow::Initlize()
{
	UpdateBox();
	return 0;
}

void CDieArrow::Render(CTimer* gameTime, MGraphic* graphics)
{
	CStaticObject::Render(gameTime, graphics);
}

void CDieArrow::Update(CTimer* gameTime)
{

}

void CDieArrow::UpdateBox()
{
	_box._x = _position.x - _size.x / 2;
	_box._y = _position.y + _size.y / 2;
	_box._vx = 0;
	_box._vy = 0;
	_box._width = _size.x;
	_box._height = _size.y;
}