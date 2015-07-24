#include "Megaman.h"


Megaman::Megaman()
{
}


Megaman::~Megaman()
{
}

void Megaman::Init(MContent* content)
{
	this->img = content->LoadTexture("Resources\\Megaman\\Megaman_Final.png");
	this->position = D3DXVECTOR2(50, 36);

	this->speed = D3DXVECTOR2(0, 0);
	this->speedmax = D3DXVECTOR2(80, 300);

	width = 24;
	height = 24;

	curframe = 0;
	framecount = 4;
	anidelay = 8;
	anicount = 0;

	rowtop = 0;
	column = 5;
	//bool
	shot = false;
	

	right = true;
	keyxpressed = false;


	for (int i = 0; i < 5; i++)
	{
		Bullets* newbullets = new Bullets(content);
		listbullets.push_back(newbullets);
	}
	countshot = 0;
	shotdelay = 15;
}

void Megaman::UpdateKeyBoard(MKeyboard* key)
{
#pragma region LeftRight
	if (key->IsKeyDown(DIK_LEFT) && !key->IsKeyDown(DIK_RIGHT))
	{
		right = false;

		if (this->speed.x > (-1)*speedmax.x)
		{
			this->speed.x -= 20;
		}
		if (++anicount > anidelay)
		{
			anicount = 0;
			if (++curframe > framecount)
			{
				curframe = 1;
			}
		}

	}
	if (key->IsKeyDown(DIK_RIGHT) && !key->IsKeyDown(DIK_LEFT))
	{
		right = true;

		if (this->speed.x < speedmax.x)
		{
			this->speed.x += 20;
		}
		if (++anicount > anidelay)
		{
			anicount = 0;
			if (++curframe > framecount)
			{
				curframe = 1;
			}
		}

	}
#pragma endregion
	if (key->IsKeyDown(DIK_X) && jump == false)
	{
		speed.y += 200;
		jump = true;
	}

	if (key->IsKeyDown(DIK_Z) && shot == false)
	{
		Fire();
	}
}

void Megaman::Fire()
{
	shot = true;
	for (int i = 0; i < 5; i++)
	{
		if (listbullets[i]->shot == false)
		{
			listbullets[i]->IsShot(this->position, this->right);
			break;
		}
	}
}

void Megaman::UpdateBullets(float gametime, Camera* cam)
{
	if (++countshot > shotdelay)
	{
		countshot = 0;
		shot = false;
	}
	for (int i = 0; i < 5; i++)
	{
		if (listbullets[i]->shot == true)
		{
			listbullets[i]->Update(gametime, cam);
		}
	}
}

void Megaman::UpdateAnimation()
{
	if (jump)
	{

		if (shot == true)
		{
			rowtop = 78;
			curframe = 0;
			width = 29;
			height = 30;
		}
		else
		{
			rowtop = 48;
			curframe = 0;
			width = 26;
			height = 30;
		}
	}
	else
	{
		if (speed.x == 0)
		{
			curframe = 0;
			width = 24;
			height = 24;
		}
		if (shot == true)
		{
			rowtop = 24;
			width = 30;
			height = 24;

		}
		else
		{
			width = 24;
			height = 24;
			rowtop = 0;
		}
	}
}

void Megaman::Update(float gameTime, MKeyboard* key, Camera* Cam, vector<GameObject*> listGameObject)
{
	Cam->Update(position);
	this->UpdateKeyBoard(key);
	this->UpdateBullets(gameTime, Cam);
	this->UpdateAnimation();
	this->UpdateBox();
	this->UpdatePos(gameTime);
	this->UpdateCollision(listGameObject, gameTime);

	this->position.x += speed.x*gameTime;
}

void Megaman::UpdatePos(float gameTime)
{	
	if (speed.x > 0)
	{
		speed.x -= 10;
	}
	if (speed.x < 0)
	{
		speed.x += 10;
	}

	position.y += speed.y*gameTime;
	if (jump)
	{
		speed.y -= 10;
	}
	if (position.y < 0)
	{
		position.y = 0;
		jump = false;
	}
}

void Megaman::UpdateCollision(vector<GameObject*> vecGameObjs, float timeFrame)
{

	float timeCollision = timeFrame;
	float normalx = 0.0f, normaly = 0.0f;

	float topTime, leftTime, rightTime, botTime;
	topTime = leftTime = rightTime = botTime = timeFrame;
	GameObject* topObj = NULL;
	GameObject* leftObj = NULL;
	GameObject* rightObj = NULL;
	GameObject* botObj = NULL;

	for (int i = 0; i < vecGameObjs.size(); i++)
	{
		GameObject* gameObj = vecGameObjs[i];
		normalx = 0.0f, normaly = 0.0f;
		float t = CheckCollision(gameObj, normalx, normaly, timeFrame);
		if (t <= timeFrame)   // Có x?y ra va ch?m.
		{
			switch (gameObj->GetID())
			{
			case 1:
				if (normaly == 1 && t < topTime)
				{
					botTime = t;
					botObj = gameObj;
				}
				else if (normaly == -1 && t < topTime)
				{
					topTime = t;
					topObj = gameObj;
				}
				else if (normalx == -1 && t < leftTime)
				{
					leftTime = t;
					leftObj = gameObj;
				}
				else if (normalx == 1 && t < rightTime)
				{
					rightTime = t;
					rightObj = gameObj;
				}
				break;
			}
		}
	}
	if (topObj != NULL)
		RespondTopGroundCollision(topObj, topTime);
	if (leftObj != NULL)
		RespondLeftGroundCollision(leftObj, leftTime);
	if (rightObj != NULL)
		RespondRightGroundCollision(rightObj, rightTime);
	if (botObj != NULL)
		RespondBotGroundCollision(botObj, rightTime);
}

void Megaman::RespondTopGroundCollision(GameObject* gameObject, float topTime)
{
	switch (gameObject->GetID())
	{
	case 1:
		break;
	}
}

void Megaman::RespondLeftGroundCollision(GameObject* gameObject, float leftTime)
{
	switch (gameObject->GetID())
	{
	case 1:
		break;
	}
}

void Megaman::RespondRightGroundCollision(GameObject* gameObject, float rightTime)
{
	switch (gameObject->GetID())
	{
	case 1:
		break;
	}
}

void Megaman::RespondBotGroundCollision(GameObject* gameObject, float topTime)
{
	switch (gameObject->GetID())
	{
	case 1:
		position.y = gameObject->GetPos().y + gameObject->height;
		speed.y = 0;
		jump = false;
		break;
	}
}


void Megaman::Render(MGraphic* graphic, Camera* cam)
{
	//*width, + width do m?i frame có kích thu?c là 48 pixel

	rect.left = (curframe%column)*width;
	rect.top = rowtop;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	D3DXVECTOR3 center((float)width / 2, (float)height / 2, 0);
	if (right == true)
	{
		graphic->DrawTexture(this->img, position, center, rect, D3DCOLOR_XRGB(255, 255, 255), cam);
	}
	else
	{
		if (shot == false)
		{

			graphic->DrawTextureFlipx(this->img, position, center, rect, D3DCOLOR_XRGB(255, 255, 255), cam);
		}
		else
		{
			if (jump)
			{
				graphic->DrawTextureFlipx(this->img, D3DXVECTOR2(position.x, position.y), center, rect, D3DCOLOR_XRGB(255, 255, 255), cam);
			}
			else
			{
				graphic->DrawTextureFlipx(this->img, D3DXVECTOR2(position.x - 8, position.y), center, rect, D3DCOLOR_XRGB(255, 255, 255), cam);
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (listbullets[i]->shot == true)
		{
			listbullets[i]->Render(graphic, cam);
		}
	}
}