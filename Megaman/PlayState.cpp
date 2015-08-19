#include "PlayState.h"


CPlayState::CPlayState(char *pathmap, MGraphic* gra, LPDIRECT3DDEVICE9 d3ddev, MKeyboard* input, Camera* cam, int id)
{
		cam->LoadCameraPath(id);
		this->_camera = cam;
		this->_graphic = gra;
		_graphic->GetCam(cam);
		_graphic->SetDevice(d3ddev);
		content = new MContent(gra->GetDevice());
		this->SetInput(input);


		_rockman.Initlize();
		_changingScreen = 0;
		_pointAfterDoor = D3DXVECTOR2(0, 0);
		_pointBeforeDoor = D3DXVECTOR2(0, 0);
		_isBossDied = false;
		LoadMap();



		// Khởi động trạng thái
		_playState = PlayState::READY;
		_deltaClearPoint = 0;
		_strClearPoint = "";
		_strBonus = "";
		_deltaTime = 0;
		_typeID = ID_SCREEN_PLAY;
		_prepareForBoss = 0;
		_shakePointRand = D3DXVECTOR2(0.0f, 0.0f);
		_defaultStringColor = D3DCOLOR_XRGB(255, 255, 255);


		megaman = new Megaman();
		megaman->Initlize();

		map = new Map();
		map->Init(content);

		tileManager = new CTile(gra);
		tileManager->LoadTile(pathmap, id);

	
		//enemy
		fish = new CEnemyFish(cam->_pos.y - 112);
		fish->_position = D3DXVECTOR2(200, cam->_pos.y - 112);
		fish->_id = 4;
		fish->_size = D3DXVECTOR2(16,16);
		fish->Initlize();

		machine =  new CEnemyMachine();
		machine->_position = D3DXVECTOR2(150,150);
		machine->_id = 7;
		machine->_size = D3DXVECTOR2(16, 8);
		machine->Initlize();

		machineauto = new  CEnemyMachineAuto(34,1, ResourceManager::GetSprite(ID_SPRITE_ENEMY_MACHINE_AUTO_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ID_SPRITE_BULLET_BLUE_COLOR, ENEMYMACHINEAUTO_ORIENTATION::BOTTOM,
					D3DXVECTOR2(0 / 1000.0f, 0),
					D3DXVECTOR2((float)80, (float)10), DAME_ENEMY_MACHINE_AUTO, BLOOD_ENEMY_MACHINE_AUTO, 1 * SCORE_DEFAULT);
		machineauto->_size = D3DXVECTOR2((float)16, (float)16);
		machineauto->Initlize();
	

		eneNinja =  new CEnemyNinja();
		eneNinja->_position = D3DXVECTOR2(150,150);
		eneNinja->_id = 7;
		eneNinja->_size = D3DXVECTOR2(26, 24);
		eneNinja->Initlize();

		megaman->_position = D3DXVECTOR2(100, 200);
		megaman->_behave = STAND;
}

void CPlayState::UpdateKeyboard(MKeyboard* input)
{
	
	if (_playState == PlayState::PLAYING&& _rockman._behave != Behave::DYING&&_rockman._behave != Behave::REAL_DIE&& !_rockman.IsRequireStopScreen() && _changingScreen == 0)
	{
		if (input->IsKeyDown(DIK_SPACE))
		{
			if (_isPause)
			{
				_isPause = false;
				_rockman.ReSetSKill();
				ResourceManager::ReplaySound();
			}
			else{
				ResourceManager::MuteSound();
				ResourceManager::PlayASound(ID_EFFECT_PAUSE);
				_isPause = true;
			}

		}
		if (input->IsKeyDown(DIK_RETURN))
		{
			if (!_isPause)
			{
				_rockman.ReSetSKill();
				_isChosingSkill = true;
				CScreenManager::GetInstance()->ShowPopupScreen(new CPopup(&_rockman, this->_graphic));
				ResourceManager::PlayASound(ID_EFFECT_POPUP_APPEAR);
			}
		}
	}
}

void CPlayState::Update(CTimer* gameTime)
{
	if (!_isPause)
	{
		///Nếu của sổ chọn skill đang mở
		if (_isChosingSkill)
		{
			_isChosingSkill = false;

			int countPowerEnegy = _powerEnegies.size();
			for (int i = 0; i < countPowerEnegy; i++)
				switch (_powerEnegies[i]->_typeID)
			{
				case ID_BAR_WEAPONS_BOOM:
				case ID_BAR_WEAPONS_CUT:
				case ID_BAR_WEAPONS_GUTS:
					_powerEnegies.erase(_powerEnegies.begin() + i);
					countPowerEnegy -= 1;
					i -= 1;
					break;
			}
			switch (_rockman.GetCurrentSkill())
			{
			case Skill::CUT:
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_WEAPONS_CUT, &_rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_CUT_VERTICAL), D3DXVECTOR2(19, -37), 0, WEASPON_DEFAULT, WEASPON_DEFAULT));
				break;
			case Skill::GUTS:
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_WEAPONS_GUTS, &_rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_GUTS_VERTICAL), D3DXVECTOR2(19, -37), 0, WEASPON_DEFAULT, WEASPON_DEFAULT));
				break;
			case Skill::BOOM:
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_WEAPONS_BOOM, &_rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_BOOM_VERTICAL), D3DXVECTOR2(19, -37), 0, WEASPON_DEFAULT, WEASPON_DEFAULT));
				break;
			}
			
		}


	}


	_input->Active();

	vector<CBullet*> bullets = megaman->GetBullets();
	for (int i = 0; i < bullets.size(); i++)
		_bulletsRockman.push_back(bullets[i]);

	for (int i = 0; i < bullets.size(); i++)
		_bulletsRockman[i]->Update(gameTime);


	megaman->Update(gameTime);
	fish->Update(gameTime,megaman);
	machine->Update(gameTime,megaman);
	machineauto->Update(gameTime,megaman);
	eneNinja->Update(gameTime,megaman);
}

void CPlayState::Draw(CTimer* gameTime, MGraphic* graphics)
{
	tileManager->RenderTile(graphics,this->_camera);
	
	map->Render(graphics,this->_camera);
	
	tileManager->RenderTile(graphics,this->_camera);

	fish->Render(gameTime,graphics);

	machine->Render(gameTime,graphics);

	machineauto->Render(gameTime,graphics);

	eneNinja->Render(gameTime,graphics);

	megaman->Render(gameTime, graphics);

	for (int i = 0; i < _bulletsRockman.size(); i++)
		_bulletsRockman[i]->Render(gameTime, graphics);

}

CPlayState::~CPlayState(void)
{
}

void CPlayState::RenderBackground(MGraphic* graphics, RECT viewport)
{

}
void CPlayState::LoadMap()
{

}
float CPlayState::CheckCollision(CGameObject* obj1, CGameObject* obj2, CDirection &normalX, CDirection &normalY, float frameTime)
{
	return 0;
}

void CPlayState::ChangeScreen(CDirection direction)
{

}

void CPlayState::FindScene(unsigned int startIndex)
{

}



