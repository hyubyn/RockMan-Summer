//-----------------------------------------------------------------------------
// File: CScreenManager.h
//
// Desc: Định nghĩa lớp CScreenManager hỗ trợ quản lý các màn hình
//
//-----------------------------------------------------------------------------
#ifndef _CSCREEN_MANAGER_H_
#define _CSCREEN_MANAGER_H_

#include <vector>
#include <iostream>
#include "Screen.h"
#include "MKeyboard.h"
#include "Timer.h"
#include "MGraphic.h"


using namespace std;

class CScreenManager{
	
	static CScreenManager*	_instance;

public:

	CScreenManager();
	~CScreenManager();

	static CScreenManager* GetInstance();

	void SetStartScreen(CScreen* screen);
	//-----------------------------------------------------------------------------
	// Summary: Phương thức vẽ màn hình và các thành phần con bên trong
	//-----------------------------------------------------------------------------
	void Render(CTimer* gameTime, MGraphic* graphics);

	//-----------------------------------------------------------------------------
	// Summary: Phương thức cập nhật màn hình và các thành phần con bên trong
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime);

	//-----------------------------------------------------------------------------
	// Summary: Phương thức cập nhật màn hình và các thành phần con bên trong
	//-----------------------------------------------------------------------------
	void UpdateInput(MKeyboard* input);
	
	//-----------------------------------------------------------------------------
	// Summary: Phương thức lấy màn hình hiện tại đang được xử lý
	//-----------------------------------------------------------------------------
	CScreen* GetCurrentScreen();

	//-----------------------------------------------------------------------------
	// Summary: Hiện thị màn hình popup
	//-----------------------------------------------------------------------------
	void ShowPopupScreen(CScreen* popupScreen);

private:
	
	//-----------------------------------------------------------------------------
	// màn hình hiện tại
	//-----------------------------------------------------------------------------
	CScreen*	_currentScreen;

	
	//-----------------------------------------------------------------------------
	// Màn hình popup
	//-----------------------------------------------------------------------------
	CScreen*	_popupScreen;

	vector<CScreen*>	_screenItems;
};

#endif //!_CSCREEN_MANAGER_H_