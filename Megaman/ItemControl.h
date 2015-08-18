#pragma once

#include "Camera.h"
#include "Timer.h"
#include "MGraphic.h"
#include "Global.h"
#include <vector>

class CItemControl
{
public:
	CItemControl(void);
	virtual ~CItemControl(void);

	//-----------------------------------------------------------------------------
	// 	Khởi tạo tất cả các thành phần của 1 đối tượng với các giá trí đã có
	//	
	//	Trả về 0 nếu lối hoặc 1 nếu thành công
	//-----------------------------------------------------------------------------
	virtual int Initlize(MGraphic* graphic) = 0;

	//-----------------------------------------------------------------------------
	// 	Vẽ tất cả các thành phần của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//	+ graphics	: cọ vẽ đối tượng
	//-----------------------------------------------------------------------------
	virtual void Render(CTimer* gameTime,Camera* cam, MGraphic* graphics) = 0;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	virtual void Update(CTimer* gameTime) = 0;
	

	//-----------------------------------------------------------------------------
	// Lấy khung hình chữ nhật bao đối tượng
	//-----------------------------------------------------------------------------
	RECT GetBoundingRectangle();

	//Lấy vị trí của đối tượng tính tại tâm
	D3DXVECTOR2 GetPositionCenter();


	D3DXVECTOR2 _position;	// Vị trí vẽ đối tượng
	
	D3DXVECTOR2	_centerposition;	// Vị trí tâm vẽ đối tượng

	D3DXVECTOR2	_size;		// Kích thước đối tượng

protected:
};

