﻿#include "CEnemyBubble.h"

CEnemyBubble::CEnemyBubble(int id, int typeID, CSprite sprite, CSprite spriteExplodingEffect, D3DXVECTOR2 v, D3DXVECTOR2 positionBegin, int dame, int blood, int score) :CEnemy()
{
	_id = id;
	_typeID = typeID;
	_sprite = sprite;
	_v = v;
	_vOriginal = v;
	_dame = dame;
	_blood = blood;
	_score = score;
	_position = positionBegin;
	_isHitDame = false;

	_spriteExplodingEffect = spriteExplodingEffect;
}

CEnemyBubble::~CEnemyBubble()
{
}

int CEnemyBubble::Initlize()
{
	_origin = D3DXVECTOR2(_size.x / 2, _size.y / 2);
	_state = ENEMYBUBBLE_STATE::NONE_ATTACK;
	UpdateBox();
	return 1;
}

void CEnemyBubble::Update(CTimer* gameTime, Megaman* rockman)
{
	_sprite.Update(gameTime);
	// Nếu không trong trạng thái đang tấn công Rockman 
	// thì tiến hành kiểm tra vị trí Rockman để chuyển hướng di chuyển
	if (_state == ENEMYBUBBLE_STATE::NONE_ATTACK)
	{
		//Tính khoảng cách x từ Rockman đến EnemyBubble
		float space = rockman->GetPos().x - _position.x;
		if (space > 0)//Nếu EnemyBubble nằm phía bên trái Rockman
			_v.x = abs(_v.x);
		else//Nếu EnemyBubble nằm phía bên phải Rockman
			if (_v.x > 0)
				_v.x *= -1;
		// Nếu EnemyBubble nằm trong vùng được phép tấn công Rockman
		if (abs(space) <= SPACE_X_TO_BUBBLE_ENEMY_ATTACK)
		{

			_state = ENEMYBUBBLE_STATE::ATTACKING;//Kích hoạt trạng thái đang tấn công 
			_endAttackingBox = this->CalcEndAttackingBox(_position, rockman->GetPos() + D3DXVECTOR2(rockman->GetBox()._width / 2, rockman->GetBox()._height / 2));//Tính toán vị trí kết thúc tấn công
			this->AnalyseParabol(this->_position, rockman->GetPos() + D3DXVECTOR2(rockman->GetBox()._width / 2, rockman->GetBox()._height / 2), D3DXVECTOR2(_endAttackingBox._x, _endAttackingBox._y));
			//Tăng vận tốc EnemyBubble thêm 40pixel/s
			if (abs(space) <= SPACE_X_TO_BUBBLE_ENEMY_ATTACK / 5)
				_v.x = abs(_v.x);
			else
				if (abs(space) <= SPACE_X_TO_BUBBLE_ENEMY_ATTACK / 3)
					_v.x = (abs(_v.x) + (VX_INCREASE_OF_BUBBLE_ENEMY_ATTACKING/3.0f) / 1000.0f) * (_v.x / (abs(_v.x)));
				else
					_v.x = (abs(_v.x) + (VX_INCREASE_OF_BUBBLE_ENEMY_ATTACKING) / 1000.0f) * (_v.x / (abs(_v.x)));
		}
	}

	if (_state == ENEMYBUBBLE_STATE::ATTACKING)//Đang trong trạng thái tấn công
	{
		//Tấn công Rockman bằng cách giải hàm Parabol 
		//để tính vị trí di chuyển của EnemyBubble
		AttackRockman(gameTime->GetTime());
		this->UpdateBox();
		return;
	}
	
	_position.x += gameTime->GetTime()*_v.x;
	_position.y += gameTime->GetTime()*_v.y;
	_isHitDame = false;
	this->UpdateBox();
}

void CEnemyBubble::Render(CTimer* gameTime, MGraphic* graphics)
{
	graphics->Draw(_sprite.GetTexture(), _sprite.GetDestinationRectangle(), _position, true);

	CGameObject::Render(gameTime, graphics);
	CMoveableObject::Render(gameTime, graphics);
}

void CEnemyBubble::UpdateBox()
{
	_box._x = _position.x - _sprite.GetFrameWidth() / 2;
	_box._y = _position.y + _sprite.GetFrameHeight() / 2;
	_box._vx = _v.x;
	_box._vy = _v.y;
	_box._width = _sprite.GetFrameWidth();
	_box._height = _sprite.GetFrameHeight();
}

void CEnemyBubble::OnCollideWith(CGameObject *gameObject, CDirection normalX, CDirection normalY, float deltaTime)
{
	switch (gameObject->_typeID)
	{
	case ID_BULLET_ROCKMAN_GUTS:
	case ID_BULLET_ROCKMAN_CUT:
	case ID_BULLET_ROCKMAN_BOOM:
	case ID_BULLET_ROCKMAN_NORMAL:
		if (normalX != CDirection::NONE_DIRECT && !_isHitDame)
		{
			_isHitDame = true;
			_blood -= ((CBullet*)gameObject)->GetDame();
			if (_blood <= 0)
			{
				CExplodingEffect* explodingEffect = new CExplodingEffect(this->_position, _spriteExplodingEffect);
				explodingEffect->Initlize();
				CExplodingEffectManager::Add(explodingEffect);
			}
		}
		break;
	}
}

CEnemyBubble* CEnemyBubble::ToValue()
{
	return new CEnemyBubble(*this);
}

void CEnemyBubble::AttackRockman(float frameTime)
{
	#pragma region Vùng dừng tấn công bằng phương pháp xét vị postion của điểm dừng. Đang kích hoạt
	//Tấn công Rockman đến khi nào vị trí của EnemyBubble gặp 
	//điểm dừng tấn công - vị trí đối xứng với vị trí cũ qua trục Oy
	//(lấy y của Rockman làm gốc) thì dừng tấn công
	if (((_v.x>0 && _position.x < _endAttackingBox._x)
		|| (_v.x<0 && _position.x > _endAttackingBox._x))
		&& _position.y < _endAttackingBox._y +2)
	{
		_position.x += frameTime*_v.x;
		_position.y = _aParabol*_position.x*_position.x + _bParabol*_position.x + _cParabol;
	}
	else
	{
		_state = ENEMYBUBBLE_STATE::NONE_ATTACK;  
		_v = _vOriginal;
		_position.y = _endAttackingBox._y;
		_position.x = _endAttackingBox._x;
	}
	#pragma endregion
		
}

void CEnemyBubble::AnalyseParabol(D3DXVECTOR2 point1, D3DXVECTOR2 point2, D3DXVECTOR2 point3) 
{
	float A = point2.x*point2.x - point3.x*point3.x;
	float B = point2.x - point3.x;
	float C = point3.y - point2.y;

	float A1 = point1.x*point1.x - point3.x*point3.x;
	float B1 = point1.x - point3.x;
	float C1 = point3.y - point1.y;

	_aParabol = (B*C1 / B1 - C) / (A - B*A1 / B1);
	_bParabol = -(A1*_aParabol + C1) / B1;
	_cParabol = point3.y - _aParabol*point3.x*point3.x - _bParabol*point3.x;
}

float CEnemyBubble::CheckCollision(Box endAttackingBox, CDirection &normalX, CDirection &normalY, float frameTime)
{
	float timeCollision = frameTime;
	Box objBox = endAttackingBox;
	Box thisBox = this->GetBox();

	// Cố định lại box của object và tính lại vận tốc của box nội tại
	thisBox._vx -= objBox._vx;
	thisBox._vy -= objBox._vy;
	objBox._vx = 0;
	objBox._vy = 0;
	
	// tạo broad phase box để kiểm tra tổng quát với đối tượng đứng yên obj
	// Nếu có xảy ra va chạm, thì tiến hành kiểm tra bằng AABBSweep và đưa ra thời gian va chạm
	Box broadBox = CCollision::GetSweptBox(thisBox, frameTime);
	if (CCollision::AABBCheck(broadBox, objBox))
	{
		timeCollision = CCollision::SweepAABB(thisBox, objBox, normalX, normalY, frameTime);
		if (timeCollision == frameTime && CCollision::AABBCheck(thisBox, objBox))
			return 0;
	}
	return timeCollision;
}

Box CEnemyBubble::CalcEndAttackingBox(D3DXVECTOR2 beginAttackingPosition, D3DXVECTOR2 attackingPosition)
{
	D3DXVECTOR2 endAttackingPosition;

	float spaceX = (beginAttackingPosition.x - attackingPosition.x);
	if (spaceX < 0)
	{
		endAttackingPosition.x = attackingPosition.x + abs(spaceX);
	}
	else
	{
		endAttackingPosition.x = attackingPosition.x - abs(spaceX);
	}
	endAttackingPosition.y = beginAttackingPosition.y;
	Box resultBox(endAttackingPosition.x, endAttackingPosition.y, 0, 0, 0, 0);

	return resultBox;
}