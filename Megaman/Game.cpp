﻿#include "Game.h"


Game::Game(HINSTANCE hIns,int W,int H,char* name)
{
	this->hInstance = hIns;
	this->Width = W;
	this->Height = H;
	this->hWnd = NULL;
	strcpy_s(this->windowName,name);
}


Game::~Game(void)
{
	if (m_pTimer)
		delete m_pTimer;
}

LRESULT CALLBACK Game::WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	if(message == WM_DESTROY)
	{
		PostQuitMessage(0);
	}
	return DefWindowProc(hWnd,message,wParam,lParam);
}

bool Game::InitWindow()
{
	WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hIconSm = 0;
	wndclass.hIcon = 0;
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hInstance = this->hInstance;
	wndclass.lpfnWndProc = (WNDPROC)WndProc;
	wndclass.lpszClassName = "Game";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClassEx(&wndclass))
	{
		return false;
	}
	this->hWnd = CreateWindow("Game",this->windowName,WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,this->Width,this->Height,NULL,NULL,this->hInstance,NULL);
	if(!this->hWnd)
		return false;
	ShowWindow(this->hWnd,SW_NORMAL);
	UpdateWindow(this->hWnd);
	
	//tạo màn hình vẽ
	graphic = new MGraphic(this->hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	

	if (!graphic->InitD3D())
		return false;

	MGraphic::_pInstance = graphic;
	if (ResourceManager::Init(this->hWnd, MGraphic::GetInstance()->GetDevice()) == 0)
	{
		MessageBox(NULL, "Lỗi không khởi tạo được các đối tượng Sound", "Lỗi khởi tạo", MB_OK);
		return false;
	}
	//Chỗ này làm ẩu nên nó không logic một tí. các bạn tự fix lại	
	content = new MContent(MGraphic::GetInstance()->GetDevice());
	return true;
	
	m_pTimer = CTimer::GetInstance();
	m_pTimer->SetMaxFps((float)GAME_FPS);
	
}


void Game::InitGame()
{
	
	CGameInfo::GetInstance()->Load();

	megaman = new Megaman();
	megaman->Initlize();

	keyboard = new MKeyboard(hInstance, hWnd);
	keyboard->Init();

	Cam = new Camera();
	
	CScreenManager::GetInstance()->SetStartScreen(new CStartState(MGraphic::GetInstance()));


	back = new BackGround();
	back->Init(content);

	map = new Map();
	map->Init(content);

	tileManager = new CTile(MGraphic::GetInstance());
}

Camera* Game::GetCam()
{
	return Cam;
}

void Game::Update(CTimer* gameTime)
{	
	keyboard->GetState();
	CScreenManager::GetInstance()->UpdateInput(keyboard);
	CScreenManager::GetInstance()->Update(gameTime);
		//megaman->Update(gameTime,keyboard,Cam,map->listGameObject);
	
	
}
void Game::Render(CTimer* gameTime)
{
	MGraphic::GetInstance()->Begin();
	//tileManager->RenderTile(graphic,Cam);
	/*back->Render(graphic, Cam);*/

	//map->Render(graphic, Cam);

	//megaman->Render(graphic,Cam);
	
		//_screenManager->GetCurrentScreen()->GetCam(Cam);
	CScreenManager::GetInstance()->Render(gameTime, MGraphic::GetInstance());
	
	MGraphic::GetInstance()->End();


}
