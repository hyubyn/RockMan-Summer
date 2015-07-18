#pragma once
#include <d3dx9.h>
#include "MContent.h"
#include "MGraphic.h"
#include "MKeyboard.h"
#include "Camera.h"
class BackGround
{

	LPDIRECT3DTEXTURE9 img;
public:
	D3DXVECTOR2 position;
	int width;
	int height;

	RECT rect;

	BackGround();
	~BackGround();

	void Init(MContent* content);
	void Update(float gameTime, MKeyboard* key, Camera* Cam);
	void Render(MGraphic* graphic, Camera* cam);
};

