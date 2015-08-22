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

		_rockman = new Megaman();
		_rockman->Initlize();
		_changingScreen = 0;
		_pointAfterDoor = D3DXVECTOR2(0, 0);
		_pointBeforeDoor = D3DXVECTOR2(0, 0);
		_isBossDied = false;
		
		//Load map - Load quadtree
		tree = new CQuadTree();
		tree->LoadMap(id);
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
		D3DXVECTOR2 pos = cam->_listPoint.at(0);
		_rockman->SetPos(D3DXVECTOR2(pos.x + SCREEN_WIDTH / 2, pos.y));
/*
		_rockman = new _rockman();
		_rockman->Initlize();
*/
		_map = new Map();
		_map->Init(content);

		tileManager = new CTile(gra);
		tileManager->LoadTile(pathmap, id);

		bubble = new  CEnemyBubble(1, 1, ResourceManager::GetSprite(ID_SPRITE_ENEMY_BUBBLE_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			D3DXVECTOR2(50.f / 1000.0f, 0.0f / 1000.0f),
			D3DXVECTOR2(200, 100), DAME_ENEMY_BUBBLE, BLOOD_ENEMY_BUBBLE, 2.5* SCORE_DEFAULT);
		bubble->_size = D3DXVECTOR2(32, 32);
		bubble->Initlize();
		//obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
	listBubble.push_back(bubble);
		

		/*_rockman->_position = D3DXVECTOR2(100, 200);
		_rockman->_behave = STAND;*/
		_input->Active();

}

void CPlayState::UpdateKeyboard(MKeyboard* input)
{
	
	if (_playState == PlayState::PLAYING&& _rockman->_behave != Behave::DYING && _rockman->_behave != Behave::REAL_DIE&& !_rockman->IsRequireStopScreen() && _changingScreen == 0)
	{
		if (input->IsKeyDown(DIK_SPACE))
		{
			if (_isPause)
			{
				_isPause = false;
				_rockman->ReSetSKill();
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
				_rockman->ReSetSKill();
				_isChosingSkill = true;
				CScreenManager::GetInstance()->ShowPopupScreen(new CPopup(_rockman, this->_graphic));
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
			switch (_rockman->GetCurrentSkill())
			{
			case Skill::CUT:
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_WEAPONS_CUT, _rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_CUT_VERTICAL), D3DXVECTOR2(19, -37), 0, WEASPON_DEFAULT, WEASPON_DEFAULT));
				break;
			case Skill::GUTS:
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_WEAPONS_GUTS, _rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_GUTS_VERTICAL), D3DXVECTOR2(19, -37), 0, WEASPON_DEFAULT, WEASPON_DEFAULT));
				break;
			case Skill::BOOM:
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_WEAPONS_BOOM, _rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_BOOM_VERTICAL), D3DXVECTOR2(19, -37), 0, WEASPON_DEFAULT, WEASPON_DEFAULT));
				break;
			}
			
		}

		if (_isStopScreen)
		{
			_deltaTimeStopScreen += gameTime->GetTime();
			if (_deltaTimeStopScreen >= 1000)
			{
				_isStopScreen = false;
				_rockman->_isRequireStopScreen = false;
			}
			else return;
		}


	}
	vector<CBullet*> bullets = _rockman->GetBullets();
	for (int i = 0; i < bullets.size(); i++)
		_bulletsRockman.push_back(bullets[i]);

	for (int i = 0; i < bullets.size(); i++)
		_bulletsRockman[i]->Update(gameTime);
	_rockman->Update(gameTime, _input);
	_camera->Update(_rockman->_position);
	tree->_listObjectOnScreen.clear();
	tree->ClipCamera(tree->_nodeRoot, _camera->getViewPort());
	

	_groundObjs.clear();
	_elevators.clear();
	//_enemies.clear();
	_items.clear();

	// lay danh sach cac doi tuong chia ra theo tung loai
	for(map<int,CGameObject*>::iterator i = tree->_listObjectOnScreen.begin();i != tree->_listObjectOnScreen.end();++i)
	{
		switch ((*i).second->_typeID)
		{
		case ID_ROCK_IN_GUT_STAGE:
		case ID_ROCK:
			if (((CRock*)(*i).second)->IsGot())
				_groundObjs.push_back((*i).second);
				break;
		case  ID_BLOCK_TROUBLE_OF_ELEVATOR:
		case ID_BLOCK:
		case ID_STAIR:
		case ID_FALLING_POINT:
		case ID_DIE_ARROW:
			_groundObjs.push_back((*i).second);
			break;
		case ID_DOOR1_CUTMAN:
		case ID_DOOR2_CUTMAN:
		case ID_DOOR1_GUTSMAN:
		case ID_DOOR2_GUTSMAN:
		case ID_DOOR1_BOOMMAN:
		case ID_DOOR2_BOOMMAN:
			_door = ((CDoor*)((*i).second));
			break;
		case ID_ITEM_BLOOD_BIG:
		case ID_ITEM_BLOOD_SMALL:
		case ID_ITEM_LIFE:
		case ID_ITEM_MANA_BIG:
		case ID_ITEM_MANA_SMALL:
			{
				bool existed = false;

				for (int j = 0; j < _items.size(); j++)
				{
					if ((*i).second->_id == _items[j]->_id)
					{
						existed = true;
						break;
					}
				}
				if (!existed)
					_items.push_back(((CItemObject*)((*i).second)->ToValue()));
				break;
			}
		case ID_ELEVATOR_TROUBLE:
		case ID_ELEVATOR:
			{
				bool existed = false;
				for (int j = 0; j < _elevators.size(); j++)
				{
					if ((*i).second->_id == _elevators[j]->_id)
					{
						existed = true;
						break;
					}
				}
				if (!existed)
					_elevators.push_back((CElevator*)((*i).second));
			}
			break;
		case ID_CUTMAN:
			if (_prepareForBoss == 0)
			{
				_prepareForBoss = 1;
				//_deltaTime = 0;
				_spriteIntroBoss = ResourceManager::GetSprite(ID_SPRITE_ROOM_CUT_STAGE);
			}
		case ID_BOOMMAN:
			if (_prepareForBoss == 0)
			{
				_prepareForBoss = 1;
				//_deltaTime = 0;
				_spriteIntroBoss = ResourceManager::GetSprite(ID_SPRITE_ROOM_BOOM_STAGE);
			}
		case ID_GUTSMAN:
			if (_prepareForBoss == 0)
			{
				_prepareForBoss = 1;
				//_deltaTime = 0;
				_spriteIntroBoss = ResourceManager::GetSprite(ID_SPRITE_ROOM_GUTS_STAGE);
			}
			if (_isBossDied)
				break;
			if (_prepareForBoss == 2 && _camera->_pos == _camera->_positionBossRoom )
			{
				bool exited = false;

				for (int j = 0; j < _enemies.size(); j++)
				{
					if ((*i).second->_id == _enemies[j]->_id)
					{
						exited = true;
						break;
					}
				}
				if (!exited)
					_enemies.push_back(((CEnemy*)(*i).second->ToValue()));

			}
			break;
		default:
			bool existed = false;

			for (int j = 0; j < _enemies.size(); j++)
			{
				if ((*i).second->_id == _enemies[j]->_id)
				{
					existed = true;
					break;
				}
			}
			if (!existed)
				_enemies.push_back(((CEnemy*)(*i).second->ToValue()));
			break;
		}
	}

	if (_playState == PlayState::READY)
	{
#pragma region Xử lý khởi động màn chơi PlayState::READY
		_deltaTime += gameTime->GetTime();
		if (_deltaTime >= 1000)
		{
			_rockman->Update(gameTime);

			CDirection normalX, normalY;
			float collideTime;

			for (int i = 0; i < _groundObjs.size(); i++)		// Kiểm tra va chạm với các khối tường, gạch đá
			{
				collideTime = CheckCollision(_rockman, _groundObjs[i], normalX, normalY, gameTime->GetTime());
				if (collideTime < gameTime->GetTime())
					_rockman->OnCollideWith(_groundObjs[i], normalX, normalY, collideTime);
			}

			// Đảm bảo rockman đã chuyển sang chế độ play,
			if (!_rockman->_isTheFirstTime)
			{
				_playState = PlayState::PLAYING;
				_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_BLOOD_ROCKMAN, _rockman, ResourceManager::GetSprite(ID_SPRITE_BAR_ROCKMAN_VERTICAL), D3DXVECTOR2(27, -37), 0, BLOOD_DEFAULT, BLOOD_DEFAULT));
				return;
			}
		}
#pragma endregion
	}

	{
#pragma region Xử lý khi vào phòng boss

		if (_prepareForBoss == 1)
		{
			_deltaTime += gameTime->GetTime();
			if (_deltaTime >= 3000)
			{
				_prepareForBoss = 2;
				_deltaTime = 0;
				_playState = PlayState::PLAYING;
			}
		}

#pragma endregion

#pragma region Xử lý chạy game
		if (_rockman->IsDied())
		{
			_playState = PlayState::GAMEOVER;
			_bulletsRockman.clear();
			ResourceManager::PlayASound(ID_EFFECT_ROCKMAN_DIE);
			ResourceManager::StopSound(ID_SOUND_BOSS);
			switch (CGameInfo::GetInstance()->GetLevel())
			{
			case ID_LEVEL_BOOM:
				ResourceManager::StopSound(ID_SOUND_BOMBMAN_STAGE);
				break;
			case ID_LEVEL_CUT:
				ResourceManager::StopSound(ID_SOUND_CUTMAN_STAGE);
				break;
			case ID_LEVEL_GUTS:
				ResourceManager::StopSound(ID_EFFECT_ELEVATOR_RUNNING);
				ResourceManager::StopSound(ID_SOUND_GUTSMAN_STAGE);
				break;
			}
			_deltaTime = 0;						// Bắt đầu đếm thời gian chờ chuyển màn
			return;
		}

		if (_door != NULL)
		{
			if (_door->_typeID == ID_DOOR1_CUTMAN ||
				_door->_typeID == ID_DOOR2_CUTMAN ||
				_door->_typeID == ID_DOOR1_GUTSMAN ||
				_door->_typeID == ID_DOOR2_GUTSMAN ||
				_door->_typeID == ID_DOOR1_BOOMMAN ||
				_door->_typeID == ID_DOOR2_BOOMMAN)
			{
				switch (_door->_typeID)
				{
				case ID_DOOR1_CUTMAN:
				case ID_DOOR1_GUTSMAN:
				case ID_DOOR1_BOOMMAN:
					//_pointBeforeDoor = _door->_position - D3DXVECTOR2(SCREEN_WIDTH / 2, 0);
					//_pointAfterDoor = _door->_position + D3DXVECTOR2(SCREEN_WIDTH / 2 + _door->GetBox()._width / 2, 0);
					break;
				case ID_DOOR2_CUTMAN:
				case ID_DOOR2_GUTSMAN:
					//_pointBeforeDoor = _door->_position - D3DXVECTOR2(SCREEN_WIDTH / 2, 0);
					//_pointAfterDoor = _camera->_listPoint.at(_camera->_listPoint.size()-1);
					break;
				case ID_DOOR2_BOOMMAN:
					//_pointBeforeDoor = _door->_position + D3DXVECTOR2(0, SCREEN_HEIGHT / 2);
					//_pointAfterDoor = _camera->_listPoint.at(_camera->_listPoint.size()-1);
					break;
				}
				_pointDoor = _door->_position;

				if (_rockman->IsRequireOpenDoor())
				{
					if (_door->GetState() == DoorState::WAITING)
					{
						_doorState = -1;
						_door->OpenDoor();
						ResourceManager::PlayASound(ID_EFFECT_OPEN_THE_DOOR);
					}
					_door->Update(gameTime);

					if (_door->GetState() == DoorState::WAITING_FOR_THROUGH&&!_rockman->IsGoingOverDoor())
					{
						_doorState = 0;
						_rockman->ThroughOverDoor(_door->_typeID);
						_changingScreen = 1;

						_enemies.clear();
						_bulletsEnemy.clear();
						_bulletsRockman.clear();
						_items.clear();
						_rockman->_canFire = true;

						if (_door->_typeID != ID_DOOR2_BOOMMAN)
						{
							_newScreenPosition = _pointAfterDoor;
							_changeScreenDirection = CDirection::ON_RIGHT;
						}
					}
				}
				else if (_rockman->IsOverDoor() && _door->GetState() == DoorState::WAITING_FOR_THROUGH)
				{
					_door->CloseDoor();
					ResourceManager::PlayASound(ID_EFFECT_OPEN_THE_DOOR);
					_door->Update(gameTime);
				}
			}

			_door->Update(gameTime);
		}
		// Chặn mọi hoạt động khi cửa hoạt động
		if (_doorState == -1)
			return;

		_rockman->Update(gameTime);

		vector<CBullet*> bullets = _rockman->GetBullets();
		for (int i = 0; i < bullets.size(); i++)
			_bulletsRockman.push_back(bullets[i]);

		// Duyệt va chạm giữa Rockman và các đối tượng trên màn hình
		CDirection normalX, normalY;
		float collideTime;

		for (int i = 0; i < _groundObjs.size(); i++)		// Kiểm tra va chạm với các khối tường, gạch đá
		{
			collideTime = CheckCollision(_rockman, _groundObjs[i], normalX, normalY, gameTime->GetTime());
			if (collideTime < gameTime->GetTime())
				_rockman->OnCollideWith(_groundObjs[i], normalX, normalY, collideTime);
		}
		if (_door != NULL)
		{
			collideTime = CheckCollision(_rockman, _door, normalX, normalY, gameTime->GetTime());
			if (collideTime < gameTime->GetTime())
				_rockman->OnCollideWith(_door, normalX, normalY, collideTime);
		}

		for (int i = 0; i < _items.size(); i++)		// Kiểm tra va chạm với các items
		{
			collideTime = CheckCollision(_rockman, _items[i], normalX, normalY, gameTime->GetTime());
			if (collideTime < gameTime->GetTime())
				_rockman->OnCollideWith(_items[i], normalX, normalY, collideTime);
		}

		for (int i = 0; i < _elevators.size(); i++)		// Kiểm tra va chạm với các băng chuyền
		{
			_elevators[i]->Update(gameTime);

			// Kiểm tra va chạm với Rockman
			collideTime = CheckCollision(_rockman, _elevators[i], normalX, normalY, gameTime->GetTime());
			if (collideTime < gameTime->GetTime())
				_rockman->OnCollideWith(_elevators[i], normalX, normalY, collideTime);

			collideTime = CheckCollision(_elevators[i], _rockman, normalX, normalY, gameTime->GetTime());
			if (collideTime < gameTime->GetTime())
				_elevators[i]->OnCollideWith(_rockman, normalX, normalY, gameTime->GetTime() - collideTime);

			for (int j = 0; j < _groundObjs.size(); j++)		// Kiểm tra va chạm với các khối tường, gạch đá
			{
				collideTime = CheckCollision(_elevators[i], _groundObjs[j], normalX, normalY, gameTime->GetTime());
				if (collideTime < gameTime->GetTime())
					_elevators[i]->OnCollideWith(_groundObjs[j], normalX, normalY, collideTime);
			}
			if (!_elevators[i]->GetCollideRegion().IntersecWith(_camera->getViewPort()))
			{
				_elevators.erase(_elevators.begin() + i);
				i -= 1;
			}
		}

		if (_rockman->IsInBossRoom() && _prepareForBoss == 2 && _changingScreen == 0)
		{
			for (int i = 0; i < _enemies.size(); i++)
			{
				switch (_enemies[i]->_typeID)
				{
				case ID_CUTMAN:
					_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_BLOOD_CUTMAN, _enemies[i], ResourceManager::GetSprite(ID_SPRITE_BAR_CUT_VERTICAL), D3DXVECTOR2(43, -37), 0, BLOOD_CUTMAN, 0));
					ResourceManager::StopSound(ID_SOUND_CUTMAN_STAGE);
					ResourceManager::PlayASound(ID_SOUND_BOSS);
					_prepareForBoss = 3;
					return;
				case ID_BOOMMAN:
					_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_BLOOD_BOOMMAN, _enemies[i], ResourceManager::GetSprite(ID_SPRITE_BAR_BOOM_VERTICAL), D3DXVECTOR2(43, -37), 0, BLOOD_BOOMMAN, 0));
					ResourceManager::StopSound(ID_SOUND_BOMBMAN_STAGE);
					ResourceManager::PlayASound(ID_SOUND_BOSS);
					_prepareForBoss = 3;
					return;
				case ID_GUTSMAN:
					_powerEnegies.push_back(new CPowerEnergyX(ID_BAR_BLOOD_GUTSMAN, _enemies[i], ResourceManager::GetSprite(ID_SPRITE_BAR_GUTS_VERTICAL), D3DXVECTOR2(43, -37), 0, BLOOD_GUTSMAN, 0));
					ResourceManager::StopSound(ID_SOUND_GUTSMAN_STAGE);
					ResourceManager::PlayASound(ID_SOUND_BOSS);
					_prepareForBoss = 3;
					return;
				}
			}
		}
		else if (_rockman->IsRequireStopScreen())
		{
			_isStopScreen = true;
			_deltaTimeStopScreen = 0.0f;
			return;
		}
		else if (_rockman->IsEndGame())
		{
			_deltaTimeStopScreen = 0.0f;
			_playState = PlayState::WIN;
			ResourceManager::StopSound(ID_SOUND_BOSS);
			ResourceManager::PlayASound(ID_EFFECT_VICTORY);
			return;
		}





	// update cac doi tuong
	for (int i = 0; i < _groundObjs.size(); ++i)
	{
		_groundObjs.at(i)->Update(gameTime);
		_groundObjs.at(i)->UpdateBox();
	}

	for (int i = 0; i < _elevators.size(); ++i)
	{
		_elevators.at(i)->Update(gameTime);
		_elevators.at(i)->UpdateBox();
	}

	for (int i = 0; i <  _enemies.size(); ++i)
	{
		if (_enemies.at(i)->GetBox().IntersecWith(_camera->getViewPort()))
		{
			_enemies.at(i)->Update(gameTime, _rockman);
			_enemies.at(i)->UpdateBox();
		}
		
	}

	for (int i = 0; i < _items.size(); i++)
	{
		_items.at(i)->Update(gameTime);
		_items.at(i)->UpdateBox();
	}
}
}

void CPlayState::Draw(CTimer* gameTime, MGraphic* graphics)
{
	//tileManager->RenderTile(graphics,this->_camera);
	

	_map->Render(graphics,this->_camera);
	
	tileManager->RenderTile(graphics,this->_camera);

	//render object
	/*for(map<int,CGameObject*>::iterator i = tree->_listObjectOnScreen.begin();i != tree->_listObjectOnScreen.end();++i)
	{
		(*i).second->Render(gameTime,graphics);
	}*/

	for (int i = 0; i < _groundObjs.size(); ++i)
	{
		_groundObjs.at(i)->Render(gameTime, graphics);
	}

	for (int i = 0; i < _elevators.size(); ++i)
	{
		_elevators.at(i)->Render(gameTime, graphics);
	}

	for (int i = 0; i <  _enemies.size(); ++i)
	{
		_enemies.at(i)->Render(gameTime, graphics);
	}

	for (int i = 0; i < _items.size(); i++)
	{
		_items.at(i)->Render(gameTime, graphics);
	}



	//tree->Render(gameTime,graphics);
	//listBubble.at(0)->Render(gameTime,graphics);
	//bubble->Render(gameTime,graphics);
	//_enemies.at(4)->Render(gameTime, graphics);

	_rockman->Render(gameTime, graphics);

	for (int i = 0; i < _bulletsRockman.size(); i++)
		_bulletsRockman[i]->Render(gameTime, graphics);

}

CPlayState::~CPlayState(void)
{
}

void CPlayState::RenderBackground(MGraphic* graphics, RECT viewport)
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



