#include "StaticGameObject.h"


StaticGameObject::StaticGameObject()
{
}


StaticGameObject::~StaticGameObject()
{
}

void StaticGameObject::UpdateBox()
{
	this->box.x = this->position.x;
	this->box.y = this->position.y;
	this->box.width = width;
	this->box.height = height;
	this->box.vX = 0;
	this->box.vY = 0;
}

StaticGameObject::StaticGameObject(D3DXVECTOR2 _pos, int _id, int _width, int _height, MContent* content, string path) :GameObject(_pos, _id, _width, _height,speed, content, path)
{
	this->position = _pos;
	this->id = _id;
	width = _width;
	height = _height;
	this->img = content->LoadTexture(path);
	this->UpdateBox();
	this->speed = D3DXVECTOR2(0, 0);
}