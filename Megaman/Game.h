#pragma once
#include <Windows.h>
#include "MGraphic.h"
#include "MContent.h"
#include "MKeyboard.h"
#include "Megaman.h"
#include "Global.h"
#include "BackGround.h"
#include "Map.h"
#include "Tile.h"
#include "CScressnManager.h"
#include "StartState.h"
#include "SelectBossState.h"
#include "CEnemyFish.h"
#include "CGameInfo.h"
//RSManager* RSManager::instance = NULL;
class Game
{
private:
	//hinstance 
	HINSTANCE hInstance;
	//hwnd
	HWND hWnd;
	//doi tuong direct x
	int Width;
	int Height;
	char windowName[256];	

	//Khai báo đối tượng graphic
	MGraphic* graphic;
	//Khai báo đối tượng Content(Dùng để load dữ liệu)
	MContent* content;
	//Khai báo đối tượng Keyboard
	MKeyboard* keyboard;

	//đối tượng camera
	Camera* Cam;
	Camera* GetCam();


	//khai báo megaman
	Megaman* megaman;


	//khai báo map
	Map* map;

	//Tile
	CTile* tileManager;

	//background
	BackGround* back;
	//đổi tượng quản lý thời gian
	CTimer* m_pTimer;

	static HRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);

	// khai bao doi tuong enemy de test
	
public:

	CScreenManager* _screenManager;
	bool InitWindow();
	void InitGame();
	void Update(CTimer* gameTime);
	void Render(CTimer* gameTime);
	Game(HINSTANCE hIns,int W,int H,char* name);
	~Game(void);
};
