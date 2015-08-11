#include "CEnemySnapper.h"


CEnemySnapper::CEnemySnapper()
{
}
int CEnemySnapper::Initlize()
{
	_dame = DAME_ENEMY_SNAPPER;
	_timeFire = 0;
	_timeFireDefault = 1000;
	_acceptFire = false;
	_blood = 1;
	return 1;
}
void CEnemySnapper::Update(CTimer* gameTime, Megaman* rockman)
{

	if (_acceptFire&&_timeFire >= 0)
	{
		_timeFire -= gameTime->GetTime();
	}
	if (_acceptFire&&_timeFire <= 0)
	{
		_timeFire = _timeFireDefault;
		_lstBullet.clear();
		_lstBullet.push_back(new CBulletSnapper(0, ID_BULLET_ENEMY_SNAPPER, ResourceManager::GetSprite(ID_SPRITE_BULLET_ENEMY_SNAPPER), DAME_BULLET_SNAPPER, 0, D3DXVECTOR2(0, 0), 0, _position.x, _position.y, rockman->GetPos().x));
	}
	if (abs(rockman->GetPos().x - _position.x) < 50)
	{
		_acceptFire = true;
	}
	else
	{
		_acceptFire = false;
	}
	
}
void CEnemySnapper::Update(CTimer* gameTime)
{
    
}
void CEnemySnapper::Render(CTimer* gameTime, MGraphic* graphics)
{

}
void CEnemySnapper::UpdateBox()
{
	
}
void CEnemySnapper::OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime)
{
	
}
CEnemySnapper* CEnemySnapper::ToValue()
{
	return new CEnemySnapper(*this);
}
CEnemySnapper::~CEnemySnapper()
{
}
vector<CBullet*> CEnemySnapper::Fire()
{
	vector<CBullet*> result = _lstBullet;
	//Xóa hết đạn trong danh sách vì bên ngoài đã nhận rồi
	_lstBullet.clear();
	return result;
}
