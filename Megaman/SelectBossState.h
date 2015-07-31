#ifndef _CSELECTBOSS_STATE_H_
#define _CSELECTBOSS_STATE_H_


#pragma once

#include "Screen.h"
#include "CTextblock.h"
#include "CMenuItem.h"
#include "ImageItem.h"
#include "CSprite.h"
#include "PlayState.h"
class CSelectBossState: public CScreen
{
public:
	CSelectBossState(MGraphic* gra, LPDIRECT3DDEVICE9 d3ddev);
	~CSelectBossState();

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
	///Biến index boss
	int			_stageIndex;

	///Chữ 
	CTextblock	_title;

	///Hình nền background
	CImageItem	_background;

	///Boss
	CMenuItem   _boss[6];
};


#endif