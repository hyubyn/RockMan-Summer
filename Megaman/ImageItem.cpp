#include "ImageItem.h"


CImageItem::CImageItem(): CItem()
{
	_texture = NULL;
	_transparentColor = D3DCOLOR_XRGB(0, 0, 0);
}


CImageItem::~CImageItem(void)
{
	_texture->~CTexture();
}

int CImageItem::Initlize(MGraphic* graphic)
{
	_texture = new CTexture(_source, _transparentColor, graphic->GetDevice());

	_centerposition = D3DXVECTOR2(_size.x / 2, _size.y / 2);

	if (_size.x != 0 && _size.y != 0)
	{
		_boundingRect.left = _position.x;
		_boundingRect.top = _position.y;
		_boundingRect.right = _boundingRect.left + _size.x;
		_boundingRect.bottom = _boundingRect.top + _size.y;
	}
	else
	{
		_boundingRect.left = _position.x;
		_boundingRect.top = _position.y;
		_boundingRect.right = _boundingRect.left + _texture->GetWidth();
		_boundingRect.bottom = _boundingRect.top + _texture->GetHeight();
	}
	return 1;
}

void CImageItem::Update(CTimer* gameTime)
{
	if (_size.x != 0 && _size.y != 0)
	{
		_boundingRect.left = _position.x;
		_boundingRect.top = _position.y;
		_boundingRect.right = _boundingRect.left + _size.x;
		_boundingRect.bottom = _boundingRect.top + _size.y;
	}
	else
	{
		_boundingRect.left = _position.x;
		_boundingRect.top = _position.y;
		_boundingRect.right = _boundingRect.left + _texture->GetWidth();
		_boundingRect.bottom = _boundingRect.top + _texture->GetHeight();
	}
}

void CImageItem::Render(CTimer* gameTime,Camera* cam, MGraphic* graphics)
{
	
	graphics->DrawTexture(_texture->GetTexture(),_position,D3DXVECTOR3(_centerposition.x,_centerposition.y,0),_transparentColor, cam);
}
