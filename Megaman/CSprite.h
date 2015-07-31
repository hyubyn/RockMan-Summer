﻿#ifndef _CSPRITE_H_
#define _CSPRITE_H_
#include <d3dx9.h>
#include "CTexture.h"
#include "Timer.h"
class CSprite : public CTexture
{
private:

	int _index;// giá trị frame hiện tại
	int _countFrame;// tổng số frame
	int _countRow;// tổng frame trên một dòng
	int _countColumn;// tổng frame trên một cột 
	int _frameHeight;// chiều cao của mỗi frame
	int _frameWidth;// chiều dài của mỗi frame
	int _timeFrame;//
	float _tick;		// cộng dôn thời gian để chyển frame
	bool _isNextFrame;
	int _frameStart;
	int _frameEnd;
	
public:
	int _timeFrameDefault;
	CSprite();
	CSprite(char* pNamePath, int countRow, int countColumn, int countFrame, int timeframe,D3DCOLOR color,  LPDIRECT3DDEVICE9 device);
	~CSprite();
	void SetIndex(int index);
	int GetIndex();
	void NextSprite();
	void Update(CTimer* gameTime);
	RECT GetDestinationRectangle();

	int GetColum();
	int GetRow();

	int GetFrameHeight();
	int GetFrameWidth();

	int GetCountFrame();

	bool IsNextFrame();
	void Reset();
	void SetAllowAnimate(int timeFrame);

	int SetFrame(int frameStart, int frameEnd);

};
#endif