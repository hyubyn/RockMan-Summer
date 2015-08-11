﻿//-----------------------------------------------------------------------------
// File: CEnemySnapper.h
//
// Desc: Định nghĩa lớp CEnemySnapper
//
//-----------------------------------------------------------------------------
#ifndef _CENEMY_SNAPPER_H_
#define _CENEMY_SNAPPER_H_

#include "DSUtil.h"
#include "CGameObject.h"
#include "CEnemy.h"
#include "CBulletSnapper.h"
#include "Megaman.h" 


class CEnemySnapper :public CEnemy
{
public:
	
	
	CEnemySnapper();
	~CEnemySnapper();
	
	int Initlize() override;

	
	void Render(CTimer* gameTime, MGraphic* graphics) override;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	//-----------------------------------------------------------------------------
	// Lấy box, nhằm xét va chạm đối tượng, tương ứng với từng sprite ID
	//-----------------------------------------------------------------------------
	void UpdateBox() override;
	void Update(CTimer* gameTime, Megaman* rockman) override;

	//-----------------------------------------------------------------------------
	// xét va chạm 
	//-----------------------------------------------------------------------------
	void OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime) override;
	CEnemySnapper* ToValue() override;
	vector<CBullet*> Fire() override;

private:
	int _timeFire;
	int _timeFireDefault;
	boolean _acceptFire;
	vector<CBullet*> _lstBullet;

};

#endif // !_CENEMY_SNAPPER_H_
