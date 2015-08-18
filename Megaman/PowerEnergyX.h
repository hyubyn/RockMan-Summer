﻿//-----------------------------------------------------------------------------"
// File: CPowerEnergy.h
//
// Desc: Định nghĩa lớp CPowerEnergy thực hiện việc kiểm soát năng lượng, máu của nhân vật trong game
//
//-----------------------------------------------------------------------------
#ifndef _POWER_ENERGYX_H_
#define _POWER_ENERGYX_H_

#include "CGameObject.h"
#include "ResourceManager.h"
#include "Camera.h"


class CPowerEnergyX : public CGameObject
{
public:
	CPowerEnergyX(int typeID, CMoveableObject* master, CTexture textureContent, D3DXVECTOR2 positionStickOnScreen, unsigned int minValue = 0, unsigned int  maxValue = 100, unsigned int value = 0, unsigned int speed = 1);

	~CPowerEnergyX();

	//-----------------------------------------------------------------------------
	// Phương thức cập nhật màn hình theo thời gian thực
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	void UpdateCamera(Camera * camera);

	//-----------------------------------------------------------------------------
	// Phương thức vẽ màn hình và các thành phần con bên trong
	//-----------------------------------------------------------------------------
	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void SetValue(unsigned int value);

	//-----------------------------------------------------------------------------
	// Xác nhận việc tăng giá trị có hoàn tất hay chưa
	//-----------------------------------------------------------------------------
	bool IsCompleted();

	CMoveableObject* GetMaster();

private:
	unsigned int _minValue, _maxValue, _value, _expectedValue, _speed;
	D3DXVECTOR2		_positionStickOnScreen;
	CMoveableObject*	_master;

	//-----------------------------------------------------------------------------
	// Xác nhận việc tăng giá trị có hoàn tất hay chưa
	//-----------------------------------------------------------------------------
	bool _isCompleted;

	CTexture _textureBkg, _textureContent;
};

#endif // !_POWER_ENERGY_H_