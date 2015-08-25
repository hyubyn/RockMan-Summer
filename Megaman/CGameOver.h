//-----------------------------------------------------------------------------"
// File: CGameOver.h
//
// Desc: Định nghĩa lớp GameOver hiển thị khi người chơi kết thúc 3 mạng
//
//-----------------------------------------------------------------------------
#ifndef _CGAMEOVER_H_
#define _CGAMEOVER_H_

#include "Screen.h"
#include "MKeyboard.h"
#include "Timer.h"
#include "MGraphic.h"
#include "DSUtil.h"
#include "Global.h"
#include "ImageItem.h"
#include "CTextblock.h"
#include "CTexture.h"
#include "PlayState.h"
#include "SelectBossState.h"
#include "CGameInfo.h"
#include <string>

class CGameOver : public CScreen
{
public:
	CGameOver(int score, Camera* cam);
	~CGameOver();
	//-----------------------------------------------------------------------------
	// Phương thức cập nhật màn hình và các thành phần con bên trong
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
	void SetScore(int score);

private: 
	CTextblock*	_textGameOver, *_textScore, *_textContinue, *_textStageSelect;
	CImageItem*		_background, *_arrow;
	D3DCOLOR		_replaceColor;
	int _score;// biến hiển thị điểm đang có
	int _statusKey;// trạng thái của mũi tên 0 ở trên 1 là ở dưới 
	string GetStringZero(int countScore);// lấy chuổi tổng số 0 cần điền
};
#endif //_CGAMEOVER_H_
