#pragma once
#include "GameObject.h"

struct CollisionInfo
{
public:
	GameObject*	_object;
	float _normalx, _normaly;
	float _timeCollide;

	CollisionInfo();
	CollisionInfo(GameObject* object, float normalx, float normaly, float timeCollide);
};