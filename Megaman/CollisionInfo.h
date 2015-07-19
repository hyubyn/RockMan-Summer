//-----------------------------------------------------------------------------
// File: CCollisionInfo.h
//
// Desc: Định nghĩa lớp CItem có các dạng như Score, Mana, Power
//
//-----------------------------------------------------------------------------
#ifndef _COLLISION_IFNO_H_
#define _COLLISION_IFNO_H_

#include "GameObject.h"
#include "CCollision.h"

struct CollisionInfo
{
public:
	GameObject*	_object;
	CDirection		_direction;
	float			_timeCollide;

	CollisionInfo();
	CollisionInfo(GameObject* object, CDirection direction, float timeCollide);
};


#endif // !_COLLISION_IFNO_H_