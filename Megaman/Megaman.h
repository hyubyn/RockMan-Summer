#ifndef _MEGAMAN_H_
#define _MEGAMAN_H_

#include "GameObject.h"
#include "CEnemyFish.h"
#include "Bullets.h"
#include <vector>
class Megaman :	public GameObject
{
public:
	D3DXVECTOR2 speedmax;

	//frame hiện tại và số lượng frame
	int curframe;
	int framecount;
	//time delay giữa các frame
	int anidelay;
	int anicount;
	//time delay giữa các lần bắn
	int countshot;
	int shotdelay;

	int rowtop, column;

	//mảng các viên đạn
	vector<Bullets*> listbullets;
	//bool đủ thứ bool
	bool shot,right;
	bool jump, stopjump;
	bool keyxpressed;

	Box box;

	void Init(MContent* content);
	void Update(float gameTime, MKeyboard* key, Camera* Cam, vector<GameObject*> listGameObject);
	void Render(MGraphic* graphic, Camera* cam);

	void UpdateKeyBoard(MKeyboard* keyboard);
	void Fire();
	void UpdateBullets(float gametime, Camera* cam);
	
	void UpdateAnimation();

	void UpdateCollision(vector<GameObject*>, float);
	void RespondTopGroundCollision(GameObject* gameObject, float topTime);
	void RespondLeftGroundCollision(GameObject* gameObject, float leftTime);
	void RespondRightGroundCollision(GameObject* gameObject, float rightTime);
	void RespondBotGroundCollision(GameObject* gameObject, float topTime);

	void UpdatePos(float gametime);

	Megaman();
	~Megaman();
};

#endif