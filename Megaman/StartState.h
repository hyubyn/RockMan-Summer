#ifndef _CSTART_STATE_H_
#define _CSTART_STATE_H_


#pragma once
#include "Screen.h"
#include "CTextblock.h"
#include "SelectBossState.h"
#include "ImageItem.h"
#include "BackGround.h"
class CStartState: public CScreen
{
public:
	CStartState(MGraphic* gra);
	~CStartState();

	
	//-----------------------------------------------------------------------------
	// Phương thức cập nhật sự kiện bàn phím, chuột
	//-----------------------------------------------------------------------------
	void UpdateKeyboard(MKeyboard* input) override;

	//-----------------------------------------------------------------------------
	// Phương thức cập nhật màn hình theo thời gian thực
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	//-----------------------------------------------------------------------------
	// Phương thức vẽ màn hình và các thành phần con bên trong
	//-----------------------------------------------------------------------------
	void Draw(CTimer* gameTime, MGraphic* graphics) override;
	

	


	private:

	///Hình nền
	CImageItem _imgBackground;

	///Chữ PressStart
	CTextblock	*_txtPressStart;
	
	int _timeFrame;

	float _tick;

	int _isNextFrame;//Trạng thái phím đã được nhấn hay chưa? Chưa nhấn thì = 0; đã nhấn thì khác 0. Biến này cũng được dùng để thay đổi trạng thái của của frame
};

#endif