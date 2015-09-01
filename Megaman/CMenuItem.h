//-----------------------------------------------------------------------------
// File: CMenuItem.h
//
// Desc: Định nghĩa lớp CMenuItem, lớp này dùng để giúp người chơi chọn màn
//
//-----------------------------------------------------------------------------
#ifndef _CMENU_ITEM_H_
#define _CMENU_ITEM_H_

#include "ItemControl.h"
#include "MGraphic.h"
#include "CTexture.h"
#include "MKeyboard.h"
#include "Global.h"
#include "CSprite.h"

class CMenuItem :public CItemControl
{
public:
	CMenuItem();
	~CMenuItem();

	//-----------------------------------------------------------------------------
	// 	Khởi tạo tất cả các thành phần của 1 đối tượng với các giá trí đã có
	//	
	//	Trả về 0 nếu lối hoặc 1 nếu thành công
	//-----------------------------------------------------------------------------
	int Initlize(MGraphic* graphic) override;

	//-----------------------------------------------------------------------------
	// 	Vẽ tất cả các thành phần của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//	+ graphics	: cọ vẽ đối tượng
	//-----------------------------------------------------------------------------
	void Render(CTimer* gameTime,Camera* cam, MGraphic* graphics) override;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	//-----------------------------------------------------------------------------
	// 	Lấy ra màu hiển thị của chữ, vì khi kích hoạt animation thì màu chữ sẽ đổi
	//-----------------------------------------------------------------------------
	D3DCOLOR GetAnimationColor();

	//-----------------------------------------------------------------------------
	// Tên của MenuItem, nó sẽ hiển thị ngay bên dưới border 
	//-----------------------------------------------------------------------------
	string	_name;

	//-----------------------------------------------------------------------------
	// Background nền của lable
	//-----------------------------------------------------------------------------
	CTexture* _background;

	//-----------------------------------------------------------------------------
	// Border của MenuItem
	//-----------------------------------------------------------------------------
	CSprite * _border;

	//-----------------------------------------------------------------------------
	// Màu chữ
	//-----------------------------------------------------------------------------
	D3DCOLOR _foreground;

	//-----------------------------------------------------------------------------
	// Chỉ định MenuItem có được focus hay không
	//-----------------------------------------------------------------------------
	bool _isFocused;
	D3DCOLOR _replaceColor;	// Biến hỗ trợ chạy hiệu ứng chữ
private:
	D3DXVECTOR2 _borderPosition;
	D3DXVECTOR2 _positionText;
	RECT    _boundingRectBkg;
	
	float _timeAnimationText;//Thời gian vẽ của 1 màu của Text
};

#endif //!_CMENU_ITEM_H_