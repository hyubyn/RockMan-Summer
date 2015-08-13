//-----------------------------------------------------------------------------
// File: CItem.h
//
// Desc: Định nghĩa lớp CItem có tác dụng dựng tường giúp các đối tượng có thể đứng được
//
//-----------------------------------------------------------------------------
#ifndef _CITEM_H_
#define _CITEM_H_

#include "CGameObject.h"
#include "ResourceManager.h"
#include "CollisionInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class CItemEatable :public CMoveableObject
{
public:
	CItemEatable();
	CItemEatable(int _typeID, D3DXVECTOR2 position, bool itemOfBoss = false, bool isDefault = false);
	~CItemEatable();

	int Initlize() override;

	//-----------------------------------------------------------------------------
	// 	Vẽ tất cả các thành phần của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//	+ graphics	: cọ vẽ đối tượng
	//-----------------------------------------------------------------------------
	void Render(CTimer* gameTime, MGraphic* graphics) override;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	void UpdateCollision(CGameObject* obj, CDirection normalX, CDirection normalY, float collideTime, float remainCollideTime);

	void UpdateBox() override;

	void GotIt();

	bool IsGot();

	CItemEatable* ToValue() override;
private:
	bool _isGot;
	bool _isDefault;
	bool _itemOfBoss;
	int _timeAppear;
	CollisionInfo	_collisionUp, _collisionDown;
};

#endif // !_CITEM_H_