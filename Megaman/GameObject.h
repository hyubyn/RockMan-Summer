#pragma once
#include <d3dx9.h>
#include "MContent.h"
#include "MGraphic.h"
#include "MKeyboard.h"
#include "Camera.h"
#include "Global.h"
#include "Collision.h"

class GameObject
{
protected:
	D3DXVECTOR2 position;
	int id;
	LPDIRECT3DTEXTURE9 img;
public:
	D3DXVECTOR2 speed;
	int width, height;
	RECT rect;
	Box box;

	GameObject();
	~GameObject();

	GameObject(D3DXVECTOR2, int, int, int, D3DXVECTOR2, MContent*, string);

	D3DXVECTOR2 GetPos();
	int GetID();
	Box GetBox();

	virtual void Update(float gametime);
	virtual void UpdateBox();
	virtual void Render(MGraphic* graphic, Camera* cam);

	float CheckCollision(GameObject* obj, CDirection &normalX, CDirection &normalY, float timeFrame);

};

