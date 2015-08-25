#include "CGameOver.h"

CGameOver::CGameOver(int score, Camera* cam) :CScreen()
{
	this->_camera = cam;
	_score = score;
	string stringScore = std::to_string(_score);
	string stringZero = GetStringZero(stringScore.length());

	_textGameOver = new CTextblock();
	_textGameOver->_position = D3DXVECTOR2(0, SCREEN_HEIGHT);//1.4
	_textGameOver->_size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT / 4);
	_textGameOver->_text = "GAME OVER";
	_textGameOver->_color = D3DCOLOR_XRGB(255, 255, 255);
	_textGameOver->_horizontalAlignment = Alignment::CENTER;
	_textGameOver->_verticalAlignment = Alignment::BOTTOM;
	_textGameOver->Initlize(MGraphic::GetInstance());

	_textScore = new CTextblock();
	_textScore->_position = D3DXVECTOR2(0, SCREEN_HEIGHT - _textGameOver->_size.y - 40);
	_textScore->_size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_textScore->_text = stringZero + stringScore;
	_textScore->_color = D3DCOLOR_XRGB(255, 255, 255);
	_textScore->_horizontalAlignment = Alignment::CENTER;
	_textScore->_verticalAlignment = Alignment::TOP;
	_textScore->Initlize(MGraphic::GetInstance());

	_textContinue = new CTextblock();
	_textContinue->_position = D3DXVECTOR2(0, SCREEN_HEIGHT / 2);
	_textContinue->_size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_textContinue->_text = "CONTINUE";
	_textContinue->_color = D3DCOLOR_XRGB(255, 255, 255);
	_textContinue->_horizontalAlignment = Alignment::CENTER;
	_textContinue->_verticalAlignment = Alignment::TOP;
	_textContinue->Initlize(MGraphic::GetInstance());

	_textStageSelect = new CTextblock();
	_textStageSelect->_position = D3DXVECTOR2(0, _textContinue->_position.y - 40);
	_textStageSelect->_size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_textStageSelect->_text = "STAGE SELECT";
	_textStageSelect->_color = D3DCOLOR_XRGB(255, 255, 255);
	_textStageSelect->_horizontalAlignment = Alignment::CENTER;
	_textStageSelect->_verticalAlignment = Alignment::TOP;
	_textStageSelect->Initlize(MGraphic::GetInstance());

	_background = new CImageItem();
	_background->_position = D3DXVECTOR2(0, SCREEN_HEIGHT);
	_background->_size = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	_background->_source = "Resources//sprites//background_3.png";
	_background->_transparentColor = D3DCOLOR_XRGB(255, 255, 255);
	_background->Initlize(MGraphic::GetInstance());

	_arrow = new CImageItem();
	_arrow->_position = D3DXVECTOR2(SCREEN_WIDTH / 3 - 40, _textContinue->_position.y);
	_arrow->_source = "Resources//sprites//arrow.png";
	_arrow->_transparentColor = D3DCOLOR_XRGB(24, 93, 214);
	_arrow->Initlize(MGraphic::GetInstance());
	_statusKey = 1;
	_typeID = ID_SCREEN_GAME_OVER;
}

void CGameOver::UpdateKeyboard(MKeyboard* input)
{
	if (input->IsKeyDown(DIK_SPACE))
	{
		if (_statusKey == 0)
		{
			_arrow->_position = D3DXVECTOR2(_arrow->_position.x, _textContinue->_position.y);
			_statusKey = 1;
		}
		else
		{
			_arrow->_position = D3DXVECTOR2(_arrow->_position.x, _textStageSelect->_position.y);
			_statusKey = 0;
		}
	}

	if (input->IsKeyDown(DIK_RETURN))
	{
		if (_statusKey == 1)
		{
			_isFinished = true;
		switch (CGameInfo::GetInstance()->GetLevel())
		{
		case ID_LEVEL_CUT:
			_nextScreen = new CPlayState("Resources//Resources//Maps//cut_man_stage.txt", this->_graphic, this->_graphic->GetDevice(), input, this->_camera, 2);
			break;
		case ID_LEVEL_GUTS:
				_nextScreen = new CPlayState("Resources//Resources//Maps//guts_man_stage.txt", this->_graphic, this->_graphic->GetDevice(), input, this->_camera, 3);
			break;
		case ID_LEVEL_BOOM:
		_nextScreen = new CPlayState("Resources//Resources//Maps//boom_man_stage.txt", this->_graphic, this->_graphic->GetDevice(), input, this->_camera, 1);
			break;
			default:return;
		}
			
		}
		else{
			_isFinished = true;
			CGameInfo::GetInstance()->SetBonusValue(0);
			
			_nextScreen = new CSelectBossState( MGraphic::GetInstance(),  MGraphic::GetInstance()->GetDevice());
		}
	}
}
CGameOver::~CGameOver()
{
	SAFE_DELETE(_textGameOver);
}
void CGameOver::Update(CTimer* gameTime)
{
	_arrow->Update(gameTime);
}

void CGameOver::Draw(CTimer* gameTime, MGraphic* graphics)
{
	_background->Render(gameTime,this->_camera, graphics);
	_arrow->Render(gameTime,this->_camera, graphics);
	_textGameOver->Render(gameTime,this->_camera, graphics);
	_textScore->Render(gameTime,this->_camera, graphics);
	_textContinue->Render(gameTime,this->_camera, graphics);
	_textStageSelect->Render(gameTime,this->_camera, graphics);
}
string CGameOver::GetStringZero(int countScore)
{
	string temp = "";
	for (size_t i = 0; i < 7 - countScore; i++)
	{
		temp += "0";
	}
	return temp;
}
void CGameOver::SetScore(int score)
{
	_score = score;
	string stringScore = std::to_string(_score);
	string stringZero = GetStringZero(stringScore.length());
	_textScore->_text = stringZero + stringScore;
}