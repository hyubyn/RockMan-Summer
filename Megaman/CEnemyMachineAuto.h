﻿//-----------------------------------------------------------------------------
// File: CEnemyMachineAuto.h
//
// Desc: Định nghĩa lớp CEnemyMachineAuto
//
//-----------------------------------------------------------------------------
#ifndef _CENEMY_MACHINE_AUTO_H_
#define _CENEMY_MACHINE_AUTO_H_

#include "CGameObject.h"
#include "CEnemy.h"
#include "CExplodingEffectManager.h"
#include "ResourceManager.h"
#include "Megaman.h"
#include "CEnemyMachineAutoBullet.h"
#include <stdlib.h>

enum class ENEMYMACHINEAUTO_ORIENTATION
{
	TOP,
	BOTTOM
};

class CEnemyMachineAuto :public CEnemy
{
public:
	CEnemyMachineAuto(int id, int typeID, CSprite sprite, CSprite spriteExplodingEffect, int spriteIDBullet, ENEMYMACHINEAUTO_ORIENTATION orientation, D3DXVECTOR2 v, D3DXVECTOR2 positionBegin, int dame, int blood = 10, int score=SCORE_DEFAULT);
	~CEnemyMachineAuto();

	int Initlize() override;

	void Update(CTimer* gameTime, Megaman* rockman) override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void UpdateBox() override;

	void OnCollideWith(CGameObject* gameObj, CDirection normalX, CDirection normalY, float deltaTime) override;

	CEnemyMachineAuto* ToValue() override;

	vector<CBullet*> Fire() override;

private:
	// Tấn công Rockman
	void AttackRockman(float deltaTime);
	// Cho biết trạng thái là đang tấn công hay không?
	//ENEMYMACHINEAUTO_STATE _state;
	// Danh sách đạn bắn ra
	vector<CBullet*> _lstBullet;
	// Thời gian tấn công. Đơn vị là Tick
	int _timeAttackRemain;
	// Thời gian giữa 2 lần bắn đạn. Đơn vị là Tick
	int _timeDelayFireRemain;
	// Hướng canh của Enemy Machine Auto
	ENEMYMACHINEAUTO_ORIENTATION _orientation;
	// Hiệu ứng nổ
	CSprite _spriteExplodingEffect;
	//ID_SPRITE_BULLET của EnemyMachineAuto này
	int _spriteIdBullet;
	// Cho biết là đã trừ máu vì va chạm đạn chưa
	bool _isHitDame;
	// Thời gian delay animation
	int _timeDelayAnimation;
};

#endif // !_CENEMY_MACHINE_AUTO_H_