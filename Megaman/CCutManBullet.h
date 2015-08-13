#ifndef _CCUTMAN_BULLET_
#define _CCUTMAN_BULLET_

#include "CBullet.h"
#include "CSprite.h"

class CCutManBullet : public CBullet
{
public:
	CCutManBullet(int id, int typeID, CSprite sprite, int dame, D3DXVECTOR2 v, D3DXVECTOR2 beginPosition);
	~CCutManBullet();

	int Initlize() override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void Update(CTimer* gameTime) override;

	void UpdateBox();

	void OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime) override;
	//-----------------------------------------------------------------------------
	// Phương thức tạo ẩn viên đạn và restar lại các thuộc tính
	//
	//-----------------------------------------------------------------------------
	void Hide();

	//-----------------------------------------------------------------------------
	// Phương thức hủy viên đạn
	//
	//-----------------------------------------------------------------------------
	void setState();

	D3DXVECTOR2 _posRockMan; // Vị trí của rock man khi nó đứng
	D3DXVECTOR2 _posCutMan; // Vị trí của cut man khi nó đứng
	double _spBulletAndCutMan; // Khoảng cách giữa đạn và cut man
	bool _isReverse;
	bool _isHide;// ẩn viên đạn khi viên đạn trở về. 

private:
	float _speed; // tốc độ của đạn.
	void Fire(double d);
	void CheckDirectionBullet();
	CMoveableObject* _master;
};
#endif //_CCUTMAN_BULLET_