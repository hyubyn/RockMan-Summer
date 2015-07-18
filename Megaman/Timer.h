#pragma once
#include <Windows.h>
#include "Global.h"


class CTimer
{
public:
	//Thời điểm bắt đầu đếm
	__int64 m_nTimeStart;
	//Thời điểm kết thúc đếm
	__int64 m_nTimeEnd;

	static CTimer* GetInstance();

	~CTimer();

	//Phương thức lấy về khoảng thời gian (tính theo giây)
	//giữa 2 tick liên tiếp
	void GetSecondPerTick();

	//Phương thức bắt đầu đếm
	void StartCount();

	//Phương thức kết thúc đếm
	void EndCount();

	//maxFps - Thời gian frame
	void SetMaxFps(float maxFps);

	//Summary:	Phương thức trả về khoảng thời gian giữa 2 frame liên tiếp
	float GetTime();


private:

	CTimer();
	//Số tick trên một giây
	__int64 m_nCountPerSec;
	//Tỉ lệ giữa tick và giây (số giây giữa 2 tick liên tiếp)
	float m_fTimeScale;
	//Số Frame trên một giây tối đa
	float m_fLockFps;
	//Thời gian delta time tính theo giây giữa 2 frame liên tiếp
	float m_fDeltaTime;
	//Thời gian delta time trong một giây
	int m_nFrameRate;

	static CTimer* s_TimerInstance;
};