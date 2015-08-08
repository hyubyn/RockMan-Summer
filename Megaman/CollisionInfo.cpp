#include "CollisionInfo.h"


CollisionInfo::CollisionInfo()
{

}

CollisionInfo::CollisionInfo(GameObject* object, float normalx, float normaly, float timeCollide)
{
	_object = object;
	_normalx = normalx;
	_normaly = normaly;
	_timeCollide = timeCollide;
}