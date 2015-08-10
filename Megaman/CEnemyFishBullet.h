#pragma once
#include "CBullet.h"
class CEnemyFishBullet:public CBullet 
{
public:
	CEnemyFishBullet(int id, int typeID, CSprite spriteBullet, int dame, float v0, D3DXVECTOR2 beginPosition, float angleFly,int x, int y);
	~CEnemyFishBullet();
	int Initlize() override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void Update(CTimer* gameTime) override;

	void UpdateBox() override;

	void OnCollideWith(CGameObject* gameObj, CDirection normalX, CDirection normalY, float deltaTime) override;
private:
		int _timeDelete;
		int _timeDeleteDefault;
};

