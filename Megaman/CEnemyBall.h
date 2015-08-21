//-----------------------------------------------------------------------------
// File: CEnemyBall.h
//
// Desc: Định nghĩa lớp CEnemyBall
//
//-----------------------------------------------------------------------------
#ifndef _CENEMY_BALL_H_
#define _CENEMY_BALL_H_

#include "CGameObject.h"
#include "CEnemy.h"
#include "ResourceManager.h"
#include "Global.h"
#include "Megaman.h"
#include "CEnemyMachineAutoBullet.h"
#include <stdlib.h>

enum class ENEMYBALL_STATE
{
	DEFENSE,//phòng thủ
	ATTACK//tấn công
};

class CEnemyBall :public CEnemy
{
public:
	CEnemyBall(int id, int typeID, CSprite sprite, CSprite spriteExplodingEffect, float vX, D3DXVECTOR2 positionBegin, int dame, int blood = 2, int score=SCORE_DEFAULT);
	~CEnemyBall();

	int Initlize() override;

	void Update(CTimer* gameTime, Megaman* rockman) override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void UpdateBox() override;

	void OnCollideWith(CGameObject* gameObj, CDirection normalX, CDirection normalY, float deltaTime) override;

	CEnemyBall* ToValue() override;

	vector<CBullet*> Fire() override;

private:
	// Tấn công Rockman
	void AttackRockman(float deltaTime);
	// Cho biết trạng thái là đang tấn công hay không?
	ENEMYBALL_STATE _state;
	// Danh sách đạn bắn ra
	vector<CBullet*> _lstBullet;
	// Thời gian phòng thủ. Đơn vị là Tick
	int _timeDefenseRemain;
	// Thời gian tấn công. Đơn vị là Tick
	int _timeAttackRemain;
	// Hiệu ứng nổ
	CSprite _spriteExplodingEffect;
	// Cho biết là đã trừ máu vì va chạm đạn chưa
	bool _isHitDame;
};

#endif // !_CENEMY_BALL_H_