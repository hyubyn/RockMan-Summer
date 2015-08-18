//-----------------------------------------------------------------------------
// File: CItemObject.h
//
// Desc: Định nghĩa lớp CItemObject có tác dụng dựng tường giúp các đối tượng có thể đứng được
//
//-----------------------------------------------------------------------------
#ifndef _CItemObject_H_
#define _CItemObject_H_

#include "CGameObject.h"
#include "ResourceManager.h"
#include "CollisionInfo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class CItemObject :public CMoveableObject
{
public:
	CItemObject();
	CItemObject(int _typeID, D3DXVECTOR2 position, bool itemOfBoss = false, bool isDefault = false);
	~CItemObject();

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

	CItemObject* ToValue() override;
private:
	bool _isGot;
	bool _isDefault;
	bool _itemOfBoss;
	int _timeAppear;
	CollisionInfo	_collisionUp, _collisionDown;
};

#endif // !_CItemObject_H_