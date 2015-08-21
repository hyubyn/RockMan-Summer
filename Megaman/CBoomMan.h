//-----------------------------------------------------------------------------
// File: CBoomMan.h
//
// Desc: Định nghĩa lớp AI CBoomMan dùng để tạo boss Boom Man
//
//-----------------------------------------------------------------------------

#ifndef _BOOM_MAN_H_
#define _BOOM_MAN_H_    

#include "CGameObject.h"
#include "Timer.h"
#include "MGraphic.h"
#include "ResourceManager.h"
#include "CEnemy.h"
#include "Megaman.h"
#include "CBoomManBullet.h"
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>


#define RANK_BOOMMAN 50
class CBoomMan : public CEnemy
{
public:
	~CBoomMan();
	CBoomMan();

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
	void Render(CTimer* gametime, MGraphic* graphics) override;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//	+ boomMan	: đối tượng boom main
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime, Megaman* rockman) override; 
	//-----------------------------------------------------------------------------
	// 	Cập nhật khung bao bên ngoài của đối tượng
	//-----------------------------------------------------------------------------
	void UpdateBox() override;

	void OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime) override;
	//-----------------------------------------------------------------------------
	// Hành vi bán đạn của boomMan
	//-----------------------------------------------------------------------------
	vector<CBullet*> Fire();

	void GetPositioRockMan(D3DXVECTOR2 pos);

	CBoomMan* ToValue() override;

	private:
	float _gravity; // gia tốc trọng trường.
	float _timeDelay;	// thời gian delay cut man đứng bắn
	float _dieDistance; // Khoảng cách giữa các hình hiệu ứng chết
	D3DXVECTOR2 _positionOld; 
	D3DXVECTOR2 _posStartDefault; // vị trí ban đâu của boom man; 
	D3DXVECTOR2 _posRockMan;
	DIRECTIONACTION _previousDirec; // trạng thái trước đó
	DIRECTIONACTION _currentDirec; // trạng thái hiện tại

	//Hướng xảy ra va chạm với vật gần nhất
	CDirection _collideNormalX, _collideNormalY;

	float _timeHistoryCollideX; // thời gian ngắn nhất để tính quảng đường đi khi va chạm theo chieu ngang.
	float _timeHistoryCollideY; // thời gian ngắn nhất để tính quảng đường đi khi va chạm theo chieu doc.

	D3DXVECTOR2 _positionBullet;// vị trí của bullet
	CBoomManBullet* _bullet;
	//bool _isFire; // trạng thái bắn và ko bắn của boomMan
	bool _isJump;  // trạng thái jump
	float _timeFire; // Thời gian tấn công.
	float _timeStart; // thời gian start
	bool _isStartJump;
	bool _isLockRun; // dùng để khóa việc nhảy
	bool _isOneHit; //Mỗi viên đạn trúng vào boom man chỉ gây dame 1 lần.
	
	
	//-----------------------------------------------------------------------------
	// Kiểm tra các trạng thái boomMan
	// gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	void CheckStatus(CTimer* gameTime);

	//-----------------------------------------------------------------------------
	// Xử lý nhảy của boomMan
	//-----------------------------------------------------------------------------
	void JumpAI();
	friend class CBoomManBullet;
private:
	float _speed;

	bool _isCollideBullet; // bật hiểu ứng trúng đạn
	float _timeHistoryCollideXBullet; // thời gian ngắn nhất để tính quảng đường đi đạn khi va chạm theo chieu ngang.
	float _timeHistoryCollideYBullet; // thời gian ngắn nhất để tính quảng đường đi đạn khi va chạm theo chieu doc.
	CDirection _collideNormalXBullet, _collideNormalYBullet; //Hướng xảy ra va chạm với đạn gần nhất
	CBullet* _bulletRockMan; // Lưu lại đạn va chạm vào cut man
	float _timeEffectCollide; // thời gian bật hiệu ứng va chạm đạn cho cut man
};

#endif// _BOOM_MAN_H_