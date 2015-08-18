#include "CMenuItem.h"

CMenuItem::CMenuItem() :CItemControl()
{
	_background = NULL;
	_border = NULL;
	_name = "";
	_isFocused = false;
	_timeAnimationText = 0;
}

CMenuItem::~CMenuItem()
{
	_background->~CTexture();
	_border->~CSprite();
}

int CMenuItem::Initlize(MGraphic* graphic)
{
	_borderPosition = D3DXVECTOR2(_position.x + _size.x / 2, _position.y - _size.y / 2);

	_boundingRectBkg.left = 0;
	_boundingRectBkg.top = 0;
	_boundingRectBkg.right = _background->GetWidth();
	_boundingRectBkg.bottom = _background->GetHeight();


	_positionText.x = _position.x;
	_positionText.y = _position.y - _size.y;

	_replaceColor = _foreground;
	_timeAnimationText = 10;

	return 1;
}

void CMenuItem::Render(CTimer* gameTime,Camera* cam, MGraphic* graphics)
{
	D3DXVECTOR3 centerback;
	centerback.x = (_boundingRectBkg.right - _boundingRectBkg.left) / 2;
	centerback.y = (_boundingRectBkg.bottom - _boundingRectBkg.top) / 2;
	centerback.z = 0;
	D3DXVECTOR3 centerbor;
	centerbor.x = (_border->GetDestinationRectangle().right - _border->GetDestinationRectangle().left) / 2;
	centerbor.y = (_border->GetDestinationRectangle().bottom - _border->GetDestinationRectangle().top) / 2;
	centerbor.z = 0;
	// Vẽ background
	graphics->DrawTexture(_background->GetTexture(),_borderPosition,centerback,_boundingRectBkg, D3DCOLOR_XRGB(255, 255, 255),cam);
	// Vẽ border 
	graphics->DrawTexture(_border->GetTexture(), _borderPosition,centerbor, _border->GetDestinationRectangle(), D3DCOLOR_XRGB(255, 255, 255),cam);
	// Vẽ đoạn text
	graphics->DrawString(_name, _positionText, _replaceColor, false,cam);

}

void CMenuItem::Update(CTimer* gameTime)
{
	
		if (_isFocused)
		{
			_border->SetAllowAnimate(_border->_timeFrameDefault);
			_border->Update(gameTime);

		
				if (_replaceColor == _foreground)
					_replaceColor = D3DCOLOR_XRGB(252, 252, 252);
				else
					_replaceColor = _foreground;
				
		}
		else
		{
			_border->Reset();
			_replaceColor = _foreground;
			_timeAnimationText = _border->_timeFrameDefault;
		}
		_timeAnimationText = 0;
		
	
	_timeAnimationText++;
	
}

D3DCOLOR CMenuItem::GetAnimationColor()
{
	return _replaceColor;
}
