#include "CollisionInfo.h"

CollisionInfo::CollisionInfo()
{

}

CollisionInfo::CollisionInfo(GameObject* object, CDirection direction, float timeCollide)
{
	_object = object;
	_direction = direction;
	_timeCollide = timeCollide;
}