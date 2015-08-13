#ifndef _CROCK_CUT_BULLET_
#define _CROCK_CUT_BULLET_

#include "CBullet.h"
#include "CSprite.h"
#include  "Megaman.h"

class CRockCutBullet : public CBullet
{
public:
	CRockCutBullet(Megaman* master);

	~CRockCutBullet();

	int Initlize() override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void Update(CTimer* gameTime) override;

	void UpdateBox();

	
	void Destroy() override;

private:
	Megaman*	_master;
	D3DXVECTOR2		_oldPosition;
	D3DXVECTOR2		_defaultVelocity, _defaultAccelerate;

	int			_timeDelay;
	bool		_isChangedState;
	int			_timeReturn;

	float CheckCollision(CGameObject* obj1, Box staticBox, CDirection &normalX, CDirection &normalY, float frameTime);
	void Find();
};
#endif //_CCUTMAN_BULLET_