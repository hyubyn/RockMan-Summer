#include "CEnemyMachineAutoBullet.h"


CEnemyMachineAutoBullet::CEnemyMachineAutoBullet(int id, int typeID, CSprite spriteBullet, int dame, float v0, D3DXVECTOR2 beginPosition, float angleFly)
	: CBullet(id, typeID, spriteBullet, dame, D3DXVECTOR2(v0*cosf(angleFly), v0*sinf(angleFly)), beginPosition)
{
	_state = BULLET_BASE_STATE::FLYING;
}

CEnemyMachineAutoBullet::~CEnemyMachineAutoBullet()
{
}

int CEnemyMachineAutoBullet::Initlize()
{	
	_origin = D3DXVECTOR2(_size.x / 2, _size.y / 2);
	this->UpdateBox();
	return 1;
}

void CEnemyMachineAutoBullet::Update(CTimer* gameTime)
{
	if (_state == BULLET_BASE_STATE::FLYING)
	{
		_position.x += gameTime->GetTime()*_v.x;
		_position.y += gameTime->GetTime()*_v.y;
	}

	this->UpdateBox();
}

void CEnemyMachineAutoBullet::UpdateBox()
{
	_box._x = _position.x - _sprite.GetFrameWidth() / 2;
	_box._y = _position.y + _sprite.GetFrameHeight() / 2;
	_box._vx = _v.x;
	_box._vy = _v.y;
	_box._width = _sprite.GetFrameWidth();
	_box._height = _sprite.GetFrameHeight();
}

void CEnemyMachineAutoBullet::Render(CTimer* gameTime, MGraphic* graphics)
{
	if (_state == BULLET_BASE_STATE::FLYING)
		graphics->Draw(_sprite.GetTexture(), _sprite.GetDestinationRectangle(), _position, true);

	CGameObject::Render(gameTime, graphics);
}

void CEnemyMachineAutoBullet::OnCollideWith(CGameObject* gameObj, CDirection normalX, CDirection normalY, float deltaTime)
{
	
}