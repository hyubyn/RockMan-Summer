#pragma once
#include "GameObject.h"
class Bullets :
	public GameObject
{
	bool right;
public:
	bool shot;

	void Update();
	void IsShot(D3DXVECTOR2 Pos, bool r);
	void Update(float gameTime, Camera* cam);
	void Render(MGraphic* graphic, Camera* cam);
	Bullets(MContent* content);
	Bullets();
	~Bullets();
};

