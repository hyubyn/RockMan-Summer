//-----------------------------------------------------------------------------
// File: CCollisionInfo.h
//
// Desc: Định nghĩa lớp CItem có các dạng như Score, Mana, Power
//
//-----------------------------------------------------------------------------
#ifndef _COLLISION_IFNO_H_
#define _COLLISION_IFNO_H_

<<<<<<< HEAD
#include "CGameObject.h"

struct CollisionInfo
=======
CollisionInfo::CollisionInfo()
>>>>>>> e4788d124d556d1b12d746a630ee720a3eb2e6f5
{
public:
	CGameObject*	_object;
	CDirection		_direction;
	float			_timeCollide;

	CollisionInfo();
	CollisionInfo(CGameObject* object, CDirection direction, float timeCollide);
};

<<<<<<< HEAD

#endif // !_COLLISION_IFNO_H_
=======
CollisionInfo::CollisionInfo(CGameObject* object, CDirection direction, float timeCollide)
{
	_object = object;
	_direction = direction;
	_timeCollide = timeCollide;
}
>>>>>>> e4788d124d556d1b12d746a630ee720a3eb2e6f5
