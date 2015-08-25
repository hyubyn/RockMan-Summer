#include "SelectBossState.h"


CSelectBossState::CSelectBossState(MGraphic* graphic, LPDIRECT3DDEVICE9 d3ddev): CScreen()
{
	this->_graphic = graphic;
	_title._position = D3DXVECTOR2(0, SCREEN_HEIGHT+20);
	_title._size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_title._text = "SELECT\nSTAGE\n\nPRESS\nSTART";
	_title._verticalAlignment = Alignment::CENTER;
	_title._horizontalAlignment = Alignment::CENTER;
	_title._color = D3DCOLOR_XRGB(156, 252, 240);
	_title.Initlize(graphic);

	_background._position = D3DXVECTOR2(0, 256);
	_background._size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_background._source = "Resources//sprites//background_2.png";
	_background._transparentColor = D3DCOLOR_XRGB(255, 255, 255);
	_background.Initlize(graphic);

	// Màn CutMan
	_boss[0]._border = new CSprite("Resources//sprites//button_menu_state.png", 1, 2, 2, 500, D3DCOLOR_XRGB(0, 255, 0),d3ddev);
	_boss[0]._background = new CTexture("Resources//sprites//icon_master_cut_man.png", D3DCOLOR_XRGB(0, 255, 0),d3ddev);
	_boss[0]._size = D3DXVECTOR2(50, 50);
	_boss[0]._position = D3DXVECTOR2(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 130);
	_boss[0]._name = "CUTMAN";
	_boss[0]._foreground = D3DCOLOR_XRGB(156, 252, 240);
	_boss[0]._isFocused = true;
	_boss[0].Initlize(graphic);

	// Màn GutsMan
	_boss[1]._border = new CSprite("Resources//sprites//button_menu_state.png", 1, 2, 2, 500, D3DCOLOR_XRGB(0, 255, 0),d3ddev);
	_boss[1]._background = new CTexture("Resources//sprites//icon_master_guts_man.png", D3DCOLOR_XRGB(0, 255, 0),d3ddev);
	_boss[1]._size = D3DXVECTOR2(50, 50);
	_boss[1]._position = D3DXVECTOR2(SCREEN_WIDTH / 2 + 15, SCREEN_HEIGHT / 2 + 130);
	_boss[1]._name = "GUTSMAN";
	_boss[1]._foreground = D3DCOLOR_XRGB(156, 252, 240);
	_boss[1].Initlize(graphic);

	// Màn IceMan
	_boss[2]._border = new CSprite("Resources//sprites//button_menu_state.png", 1, 2, 2, 500, D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[2]._background = new CTexture("Resources//sprites//icon_master_Ice_man.png", D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[2]._size = D3DXVECTOR2(50, 50);
	_boss[2]._position = D3DXVECTOR2(SCREEN_WIDTH / 2 + 44, SCREEN_HEIGHT / 2 + 62);
	_boss[2]._name = "ICEMAN";
	_boss[2]._foreground = D3DCOLOR_XRGB(156, 252, 240);
	_boss[2].Initlize(graphic);

	// Màn BoomMan
	_boss[3]._border = new CSprite("Resources//sprites//button_menu_state.png", 1, 2, 2, 500, D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[3]._background = new CTexture("Resources//sprites//icon_master_Boom_man.png", D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[3]._size = D3DXVECTOR2(50, 50);
	_boss[3]._position = D3DXVECTOR2(SCREEN_WIDTH / 2 + 15, SCREEN_HEIGHT / 2 - 5);
	_boss[3]._name = "BOOMMAN";
	_boss[3]._foreground = D3DCOLOR_XRGB(156, 252, 240);
	_boss[3].Initlize(graphic);

	// Màn FireMan
	_boss[4]._border = new CSprite("Resources//sprites//button_menu_state.png", 1, 2, 2, 500, D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[4]._background = new CTexture("Resources//sprites//icon_master_Fire_man.png", D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[4]._size = D3DXVECTOR2(50, 50);
	_boss[4]._position = D3DXVECTOR2(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 5);
	_boss[4]._name = "FIREMAN";
	_boss[4]._foreground = D3DCOLOR_XRGB(156, 252, 240);
	_boss[4].Initlize(graphic);

	// Màn ElecMan
	_boss[5]._border = new CSprite("Resources//sprites//button_menu_state.png", 1, 2, 2, 500, D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[5]._background = new CTexture("Resources//sprites//icon_master_Electric_man.png", D3DCOLOR_XRGB(0, 255, 0), d3ddev);
	_boss[5]._size = D3DXVECTOR2(50, 50);
	_boss[5]._position = D3DXVECTOR2(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 62);
	_boss[5]._name = "ELECMAN";
	_boss[5]._foreground = D3DCOLOR_XRGB(156, 252, 240);
	_boss[5].Initlize(graphic);

	_stageIndex = 0;


}

void CSelectBossState::UpdateKeyboard(MKeyboard* input)
{

	if (input->GetKeyDown() == DIK_D  )
	{
		if(_stageIndex == 5)
			_stageIndex = 0;
		else 
			_stageIndex ++;
		_boss[_stageIndex]._isFocused = true;
		for (int i = 0; i < 6; i++)
		{
			if (i != _stageIndex)
				_boss[i]._isFocused = false;
		}
		//ResourceManager::PlayASound(ID_EFFECT_FOCUS_STAGE);
	}
	input->GetState();
	if (input->GetKeyUp() == DIK_A)
	{
		if(_stageIndex == 0)
			_stageIndex = 5;
		else 
			_stageIndex --;
		_boss[_stageIndex]._isFocused = true;
		for (int i = 0; i < 6; i++)
		{
			if (i != _stageIndex)
				_boss[i]._isFocused = false;
		}
	
	}
	if (input->IsKeyDown(DIK_RETURN)){

		switch (_stageIndex + 1)
		{
		case 1:
			CGameInfo::GetInstance()->SetLevel(ID_LEVEL_CUT);
			_nextScreen = new CPlayState("Resources//Resources//Maps//cut_man_stage.txt", this->_graphic, this->_graphic->GetDevice(), input, this->_camera, 2);
			_isFinished = true;
			
			break;
		case 2:
			CGameInfo::GetInstance()->SetLevel(ID_LEVEL_GUTS);
			_nextScreen = new CPlayState("Resources//Resources//Maps//guts_man_stage.txt", this->_graphic, this->_graphic->GetDevice(), input, this->_camera, 3);
			_isFinished = true;

			break;
		case 4:
			CGameInfo::GetInstance()->SetLevel(ID_LEVEL_BOOM);
			_nextScreen = new CPlayState("Resources//Resources//Maps//boom_man_stage.txt", this->_graphic, this->_graphic->GetDevice(), input, this->_camera, 1);
			_isFinished = true;
			
			break;
		}
	}
}


void CSelectBossState::Update(CTimer* gameTime)
{
	//if (!_isJustPlaySound)
	//{
	//	ResourceManager::StopSound(ID_SOUND_GAME_START);
	//	ResourceManager::PlayASound(ID_SOUND_STAGE_SELECT);
	//	_isJustPlaySound = true;
	//}
	for (int i = 0; i < 6; i++)
	{
		_boss[i].Update(gameTime);
	}
}


void CSelectBossState::Draw(CTimer* gameTime, MGraphic* graphics)
{

	_background.Render(gameTime, this->_camera, graphics);
	_title._color = _boss[_stageIndex].GetAnimationColor();
	_title.Render(gameTime, this->_camera, graphics);

	for (int i = 0; i < 6; i++)
		_boss[i].Render(gameTime, this->_camera, graphics);
}

CSelectBossState::~CSelectBossState()
{
}
