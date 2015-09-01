#include "StartState.h"


CStartState::CStartState(MGraphic* gra): CScreen()
{
		this->_graphic = gra;
	_txtPressStart = new CTextblock();
	_txtPressStart->_position = D3DXVECTOR2(0, 240);
	_txtPressStart->_size = D3DXVECTOR2(SCREEN_WIDTH, 224);
	_txtPressStart->_text = "PRESS START";
	_txtPressStart->_verticalAlignment = Alignment::CENTER;
	_txtPressStart->_horizontalAlignment = Alignment::CENTER;
	_txtPressStart->_color = D3DCOLOR_XRGB(255, 255, 255);
	_txtPressStart->Initlize(_graphic);



	
	_imgBackground._position = D3DXVECTOR2(0, 256);
	_imgBackground._size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_imgBackground._source = "Resources\\Terrain\\background1.png";
	_imgBackground._transparentColor = D3DCOLOR_XRGB(255, 255, 255);
	_imgBackground.Initlize(_graphic);
	_isNextFrame = 0;
	_isFinished = false;

		_tick=0;
		_timeFrame = 50;
}



void CStartState::UpdateKeyboard(MKeyboard *input)
{
		ResourceManager::PlayASound(ID_SOUND_GAME_START);
	if (input->GetKeyDown()==DIK_SPACE && _isNextFrame==0)
	{
		_isNextFrame++;
	
	}
}

void CStartState::Update(CTimer* gameTime)
{

	if (_isNextFrame>0)
	{
		_tick += gameTime->GetTime(); 
		if (_tick >= _timeFrame)
		{
			_tick = 0;
			_isNextFrame++;
		}
		
		//Tự động nháy animation 5 lần rồi chuyển màn hình GameMenu
		if (_isNextFrame >= 40)
		{
			_nextScreen = new CSelectBossState(this->_graphic, this->_graphic->GetDevice());			
			_isFinished = true;
			_isNextFrame = 0;
		}
	}
}

void CStartState::Draw(CTimer* gameTime, MGraphic* graphics)
{
	_imgBackground.Render(gameTime,this->_camera, this->_graphic );
	if (_isNextFrame>0)
	{//Bắt đầu vẽ animation
		if (_isNextFrame%8==0)//Vẽ màu trắng
		{
			_txtPressStart->_color = D3DCOLOR_XRGB(255, 255, 255);
			_txtPressStart->Render(gameTime, this->_camera, this->_graphic);
		}
		else//Vẽ màu đen
		{
			_txtPressStart->_color = D3DCOLOR_XRGB(0, 0, 0);
			_txtPressStart->Render(gameTime, this->_camera, this->_graphic);
		}
	}
	else
	{
			_txtPressStart->_color = D3DCOLOR_XRGB(255, 255, 255);
			_txtPressStart->Render(gameTime, this->_camera, this->_graphic);
	}
}

CStartState::~CStartState(void)
{
}
