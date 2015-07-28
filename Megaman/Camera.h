#pragma once
#include "d3dx9.h"
#include <vector>
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
	vector<D3DXVECTOR2> _listPoint;
	vector<MoveLine> _listMoveLine;
	bool isMoving;
	D3DXVECTOR2 endPoint;
public:
	Camera();
	~Camera();
	D3DXVECTOR2 _pos;
	RECT getViewPort();
	int width;
	int height;
	void Update(D3DXVECTOR2 megamanPos);
	void Check();
	void Move(D3DXVECTOR2,int );
	D3DXVECTOR3 GetPointTransform(int x, int y);
	void Transform(D3DXVECTOR2* position);
};

