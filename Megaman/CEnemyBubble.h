//-----------------------------------------------------------------------------
// File: CEnemyBubble.h
//
// Desc: Định nghĩa lớp CEnemyBubble
//
//-----------------------------------------------------------------------------
#ifndef _CENEMY_BUBBLE_H_
#define _CENEMY_BUBBLE_H_

#include "CGameObject.h"
#include "CEnemy.h"
#include "ResourceManager.h"
#include "Global.h"
#include "Megaman.h"
#include "CExplodingEffectManager.h"
#include <stdlib.h>

enum ENEMYBUBBLE_STATE
{
	NONE_ATTACK,
	ATTACKING
};

class CEnemyBubble :public CEnemy
{
public:
	CEnemyBubble(int id, int typeID, CSprite sprite, CSprite spriteExplodingEffect, D3DXVECTOR2 v, D3DXVECTOR2 positionBegin, int dame, int blood = 2, int score=SCORE_DEFAULT);
	~CEnemyBubble();
	
	int Initlize() override;

	void Update(CTimer* gameTime, Megaman* rockman) override;

	void Render(CTimer* gameTime, MGraphic* graphics) override;

	void UpdateBox() override;

	void OnCollideWith(CGameObject* gameObj, CDirection normalX, CDirection normalY, float deltaTime) override;

	CEnemyBubble* ToValue() override;

private:
	// Tấn công Rockman
	void AttackRockman(float frameTime);
	//Phân tích để tìm ra phương trình của Parabol đường đi tấn công của EnemyBubble
	void AnalyseParabol(D3DXVECTOR2 point1, D3DXVECTOR2 point2, D3DXVECTOR2 point3);
	//Check va chạm với EndAttackingBox 
	float CheckCollision(Box endAttackingBox, CDirection &normalX, CDirection &normalY, float frameTime);
	// Tìm Box của vị trí dừng tấn công
	Box CalcEndAttackingBox(D3DXVECTOR2 beginAttackingPosition, D3DXVECTOR2 attackingPosition);
	// Box của vị trí kết thúc trạng thái tấn công
	Box _endAttackingBox;
	// Cho biết trạng thái là đang tấn công hay không?
	ENEMYBUBBLE_STATE _state;
	// Các tham số của phương trình Parabol (Phương trình đường đi của Enemy lúc tấn công)
	float _aParabol, _bParabol, _cParabol;
	// Lưu giữ vận tốc bình thường của Enemy
	D3DXVECTOR2 _vOriginal;
	// Hiệu ứng nổ
	CSprite _spriteExplodingEffect;
	// Cho biết là đã trừ máu vì va chạm đạn chưa
	bool _isHitDame;
};

#endif // !_CENEMY_BUBBLE_H_