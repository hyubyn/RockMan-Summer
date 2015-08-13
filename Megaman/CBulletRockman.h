﻿#ifndef _BULLET_ROCKMAN_H
#define _BULLET_ROCKMAN_H

#include "CBullet.h"
#include "CSprite.h"
#include "ResourceManager.h"
#include "CollisionInfo.h"

class CBulletRockman : public CBullet
{
public:
	/*------------------------------------------
	Summary:	Khởi tạo đối tượng đạn thuần của Rockman
	+ v: Vận tốc của đạn, quy định hướng bay của đạn
	+ beginPosition: Vị trí bắt đầu bay của đạn
	Return:
	-------------------------------------------*/
	CBulletRockman(D3DXVECTOR2 v, D3DXVECTOR2 beginPosition, int typeID = ID_BULLET_ROCKMAN_NORMAL, CSprite sprite = ResourceManager::GetSprite(ID_SPRITE_BULLET_ROCKMAN_NORMAL), int dame = DAME_BULLET_ROCKMAN);
	~CBulletRockman();

	int Initlize() override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void Update(CTimer* gameTime) override;

	void OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime) override;
private:
	CollisionInfo		_collidedObject;
};
#endif //!_BULLET_ROCKMAN_H