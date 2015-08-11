//-----------------------------------------------------------------------------
// File: CEnemyInk.h
//
// Desc: Định nghĩa lớp CEnemyInk
//
//-----------------------------------------------------------------------------
#ifndef _CENEMY_INK_H_
#define _CENEMY_INK_H_

#include "CGameObject.h"
#include "CEnemy.h"
#include "ResourceManager.h"
#include "Megaman.h"
#include <iostream>
#include <string.h>
using namespace std;
class CEnemyInk :public CEnemy
{
public:

	CEnemyInk(int kindInk);
	~CEnemyInk();
	//-----------------------------------------------------------------------------
	// 	Khởi tạo tất cả các thành phần của 1 đối tượng với các giá trí đã có
	//	
	//	Trả về 0 nếu lối hoặc 1 nếu thành công
	//-----------------------------------------------------------------------------
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

	//-----------------------------------------------------------------------------
	// Lấy box, nhằm xét va chạm đối tượng, tương ứng với từng sprite ID
	//-----------------------------------------------------------------------------
	void UpdateBox() override;
	void Update(CTimer* gameTime, Megaman* rockman) override;
	
	void Jump(D3DXVECTOR2 positionRockman);
	void TestJump();
	void AnalyseParabol(D3DXVECTOR2 point1, D3DXVECTOR2 point2, D3DXVECTOR2 point3);
	void OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime) override;
	CEnemyInk* ToValue() override;
	
private:
	int _kindInk;
	int _timeJump; // thời gian mực sẽ bắt đầu reset lại khoảng nhảy, tức thời gian mực nhảy tới rockman 
	
	int _heightInk; // chiều cao mực sẽ nhảy cao so với rockman
	D3DXVECTOR2 _positionRockMan; //tọa độ rockman 
	int _between;              // điểm giữa
	int _timeStand; // thời gian kiểm tra để có thực hiện việc nhảy không (<=0 sẽ thự hiện nhảy)
	float _deltaV;
	int _timeStandDefault;// thời gian nó sẽ nghỉ thật sự 

	D3DXVECTOR2 _PositionRockMan;
	
	
	
	float _V0;
	float _g;
	float _lenghtMax;
	float _anpha;
	float _timeaddspeed;
	float _vFall;

	float _testpositiony;
	enum StaticEnemyInk
	{
		JUMP,
		STAND, 
		FALL
	};
	StaticEnemyInk _static;
	int _testbug;
	CDirection _historyCollide;
	float _timeHistoryCollide;
};

#endif // !_CENEMY_INK_H_