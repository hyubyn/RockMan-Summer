#include "ImageItem.h"


CImageItem::CImageItem(): CItemControl()
{
	_texture = NULL;
	
}


CImageItem::~CImageItem(void)
{
	_texture->~CTexture();
}

int CImageItem::Initlize(MGraphic* graphic)
{
	_texture = new CTexture(_source, _transparentColor, graphic->GetDevice());

	_centerposition = D3DXVECTOR2(0, 0);

	if (_size.x != 0 && _size.y != 0)
	{
		_boundingRect.left = 0;
		_boundingRect.top = 0;
		_boundingRect.right = _boundingRect.left + _size.x;
		_boundingRect.bottom = _boundingRect.top + _size.y;
	}
	else
	{	
		_boundingRect.left = 0;
		_boundingRect.top = 0;
		_boundingRect.right = _boundingRect.left + _texture->GetWidth();
		_boundingRect.bottom = _boundingRect.top + _texture->GetHeight();
	}
	return 1;
}

void CImageItem::Update(CTimer* gameTime)
{

}

void CImageItem::Render(CTimer* gameTime,Camera* cam, MGraphic* graphics)
{

	graphics->DrawTexture(_texture->GetTexture(),_position,D3DXVECTOR3(_centerposition.x,_centerposition.y,0),_boundingRect,_transparentColor, cam);
	//graphics->DrawTexture(_texture->GetTexture(),_position,D3DXVECTOR3(_centerposition.x,_centerposition.y,0),_transparentColor, cam);
}
