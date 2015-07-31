#ifndef _CPLAY_STATE_H_
#define _CPLAY_STATE_H_

#pragma once
#include "Screen.h"
#include "Map.h"
#include "Tile.h"
#include "Megaman.h"

class CPlayState: public CScreen

{
public:
	CPlayState(char *pathmap, MGraphic* gra, LPDIRECT3DDEVICE9 d3ddev, MKeyboard* input);

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

	~CPlayState(void);

private:
	char* mappath;

	//khai báo megaman
	Megaman* megaman;


	//khai báo map
	Map* map;

	//Tile
	CTile* tileManager;

		//Khai báo đối tượng Content(Dùng để load dữ liệu)
	MContent* content;
};

#endif

