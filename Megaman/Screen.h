#pragma once
#ifndef CSREEN_H
#define _SREEN_H

#include "MKeyboard.h"
#include "MGraphic.h"
#include "Timer.h"
#include "Camera.h"

///Class Screen là class màn hình cha để cho các màn hình con thừa kế


class CScreen
{
public:

	CScreen(void);
	~CScreen(void);

	///Phương thức cập nhật các input chính
	virtual void UpdateKeyboard(MKeyboard* keyboard) = 0;

	///Phương thức cập nhật màn hình chơi theo thời gian game
	virtual void Update(CTimer* gameTime) = 0;

	///Phương thức vẽ các content có trong mỗi màn hình
	virtual void Draw(CTimer* gameTime, MGraphic* graphics) = 0;	

	///Kiểm tra màn hình đó đã chạy xong hay chưa
	bool CheckFinished();

	///Lấy ra màn hình sẽ hiển thị tiếp theo khi màn hình hiển thị xong
	CScreen* GetNextScreen();

	///Set giá trị cho biến gra
	void GetGraphic(MGraphic* gra);

	///Set giá trị cho biến input
	void SetInput(MKeyboard* _input);

	///Set giá trị cho cho biến cam
	void GetCam(Camera* cam);

	bool IsFinished();

	friend class CScreenManager;

protected:
	Camera*		_camera;
	bool		_isFinished;
	CScreen*	_nextScreen;
	MGraphic* _graphic;
	CTimer* _gameTime;
	MKeyboard* _input;
	int				_typeID;		// ID của màn hình

};



#endif // !CSREEN_H



