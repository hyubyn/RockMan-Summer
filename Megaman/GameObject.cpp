#include "GameObject.h"


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

GameObject::GameObject(D3DXVECTOR2 _pos, int _id, int _width, int _height, D3DXVECTOR2 _speed, MContent* content, string path)
{
	this->position = _pos;
	this->id = _id;
	width = _width;
	height = _height;
	this->img = content->LoadTexture(path);
	this->speed = _speed;
}

D3DXVECTOR2 GameObject::GetPos()
{
	return this->position;
}

int GameObject::GetID()
{
	return this->id;
}

Box GameObject::GetBox()
{
	return this->box;
}

void GameObject::Update(float gametime)
{

}

void GameObject::UpdateBox()
{
	this->box._x = this->position.x;
	this->box._y = this->position.y;
	this->box._width = width;
	this->box._height = height;
	this->box._vx = speed.x;
	this->box._vy = speed.y;
}

void GameObject::Render(MGraphic* graphic, Camera* cam)
{
	rect.left = rect.top = 0;
	rect.bottom = rect.right = width;
	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);
	graphic->DrawTexture(this->img, position, center, rect, D3DCOLOR_XRGB(255, 255, 255), cam);
}

float GameObject::CheckCollision(GameObject* obj, CDirection &normalX, CDirection &normalY, float timeFrame)
{
	float timeCollision = timeFrame;
	Box myBox = this->GetBox();
	Box objBox = obj->GetBox();

	/*Box myBox(545.8f, 75.2f, 30.0f, 28.0f, 0.0f, -8.3f);
	Box objBox(576.0f, 52.0f, 128.0f, 20.0f, 0.0f, 0.0f);*/

	// Cố định objBox nếu objBox là đối tượng di chuyển.
	myBox._vx -= objBox._vx;
	myBox._vy -= objBox._vy;
	objBox._vx = 0;
	objBox._vy = 0;

	Box sweptBroadphaseBox = CCollision::GetSweptBroadphaseBox(myBox, timeFrame);

	if (CCollision::AABBCheck(sweptBroadphaseBox, objBox))
	{
		timeCollision = CCollision::SweepAABB(myBox, objBox, normalX, normalY, timeFrame);

		if (timeCollision == timeFrame && CCollision::AABBCheck(myBox, objBox))
			return 0;
	}

	return timeCollision;
}