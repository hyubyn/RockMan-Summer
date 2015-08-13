#ifndef _GUTS_ROCKMAN_BULLET_
#define _GUTS_ROCKMAN_BULLET_

#include "CBullet.h"
#include "CSprite.h"
#include  "Megaman.h"
#include "ResourceManager.h"
#include "Global.h"
#include "CRock.h"

class CGutsRockmanBullet : public CBullet
{
public:
	CGutsRockmanBullet(Megaman* master, int rockTypeID=ID_ROCK);

	~CGutsRockmanBullet();

	int Initlize() override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void Update(CTimer* gameTime) override;

	void UpdateBox();


	void Destroy() override;

private:
	Megaman*	_master;
	bool		_isAtFirst;
	int			_deltaTime;
};
#endif //_GUTS_MAN_BULLET_