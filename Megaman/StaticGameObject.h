#pragma once
#include "GameObject.h"
class StaticGameObject :
	public GameObject
{
public:

	StaticGameObject(D3DXVECTOR2, int, int, int, MContent*, string);
	
	void UpdateBox();

	StaticGameObject();
	~StaticGameObject();

};

