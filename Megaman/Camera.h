#pragma once
#include "d3dx9.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

enum DirectionCamera	// huong di chuyen cua Camera
{
	horizontal,			// huong ngang
	vertical			// huong doc

};
struct MoveLine			// duong di chuyen, bao gom huong di chuyen va toa do diem dau diem cuoi
{
	DirectionCamera direct;		// huong di chuyen
	D3DXVECTOR2 startPoint;		// toa do diem dau
	D3DXVECTOR2 endPoint;		// toa do diem cuoi
	MoveLine(D3DXVECTOR2 start, D3DXVECTOR2 end)
	{
		startPoint = start;
		endPoint = end;
		if (startPoint.x == endPoint.x)
		{
			direct = vertical;
		} 
		else
		{
			direct = horizontal;
		}
	}

	bool checkPoint(D3DXVECTOR2 positionCamera)				// kiem tra toa do camera co nam trong line ko
	{
		if (direct == horizontal)							// neu huong di chuyen la ngang thi kiem tra toa do x
		{
			if (startPoint.x <= positionCamera.x && positionCamera.x <= endPoint.x && startPoint.y == positionCamera.y)
			{
				return true;
			} 
			else
			{
				return false;
			}
		}
		else                                             // neu huong di chuyen la doc thi kiem tra toa do y
		{
			if (startPoint.x == positionCamera.x && ((startPoint.y <= positionCamera.y && positionCamera.y <= endPoint.y)||(startPoint.y >= positionCamera.y && positionCamera.y >= endPoint.y)))
			{
				return true;
			} 
			else
			{
				return false;
			}
		}
	}
};

class Camera
{
	D3DXMATRIX _MatrixTransform;
	vector<D3DXVECTOR2> _listPoint;	// list cac toa do duoc doc tu file txt
	vector<MoveLine> _listMoveLine;	// list cac duong thang ma camera di chuyen ben tren
	bool isMoving;		// bien xac dinh camera co dang di chuyen hay ko
	D3DXVECTOR2 endPoint;	// toa do camera di chuyen toi
	D3DXVECTOR2 endMap;	// toa do cuoi cung cua Camera
	int count;	// bien dem luu tru so luong point path
	int limitX; // hieu cua hai toa do camera di chuyen. moi map moi khac
public:
	Camera();
	~Camera();
	D3DXVECTOR2 _pos;
	RECT getViewPort();
	void LoadCameraPath(int id);	// Ham load file txt lay cac toa do cua camera path, id: 1 = boom state, 2 = cut state, 3 = guts state
	int width;
	int height;
	void Update(D3DXVECTOR2 megamanPos);
	void Check();
	void Move(D3DXVECTOR2,int );
	void SetEndMap(D3DXVECTOR2);				// set toa do cuoi cung cua camera
	D3DXVECTOR3 GetPointTransform(int x, int y);
	void Transform(D3DXVECTOR2* position);
};

