#include "Camera.h"
#include "Global.h"

Camera::Camera()
{
	_pos.x = 0;
	_pos.y = 256;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	isMoving = false;
	D3DXMatrixIdentity(&_MatrixTransform);
	_MatrixTransform._22 = -1;
	_listPoint.push_back(D3DXVECTOR2(0,256));
	_listPoint.push_back(D3DXVECTOR2(1535,256));
	_listPoint.push_back(D3DXVECTOR2(1535,500));
	_listPoint.push_back(D3DXVECTOR2(1535,740));
	_listPoint.push_back(D3DXVECTOR2(2815,740));
	_listPoint.push_back(D3DXVECTOR2(2815,978));
	_listPoint.push_back(D3DXVECTOR2(2815,1216));
	_listPoint.push_back(D3DXVECTOR2(3839,1216));
	_listPoint.push_back(D3DXVECTOR2(4096,1216));
	_listPoint.push_back(D3DXVECTOR2(4096, 978));
	_listPoint.push_back(D3DXVECTOR2(4096, 555));
	_listPoint.push_back(D3DXVECTOR2(4096, 320));
	for (int i = 0; i < _listPoint.size() - 1; i++)
	{
		_listMoveLine.push_back(MoveLine(_listPoint.at(i), _listPoint.at(i + 1)));
	}
}


Camera::~Camera()
{
}

void Camera::Update(D3DXVECTOR2 megamanPosition)
{
	if (!isMoving)
	{
		for (int i = 0; i < _listMoveLine.size(); ++i)
		{
			if (_listMoveLine.at(i).checkPoint(_pos))
			{
				Move(megamanPosition, i);
			}
		}
	} 
	else
	{
		if (_pos.y < endPoint.y)
		{
			_pos.y ++;
		}
		else if (_pos.y > endPoint.y)
		{
			_pos.y--;
		}
		else
		{
			isMoving = false;
		}
	}
	
}

void Camera::Move(D3DXVECTOR2 megamanPos, int index)
{
	MoveLine line = _listMoveLine.at(index);
	if (line.direct == horizontal)											// camera di chuyen theo phuong ngang
	{
		if (line.endPoint.x - line.startPoint.x < 300 && _pos.x < line.endPoint.x)	//neu la toa do camera di chuyen qua thi cho camera chay len
		{
			_pos.y = line.endPoint.y;
			_pos.x += 1;
			if (_pos.x > line.endPoint.x)
			{
				_pos.x = line.endPoint.x;
			}
		} 
		else
		{
			_pos.x = megamanPos.x - SCREEN_WIDTH / 2;
			if (_pos.x < line.startPoint.x )
			{
				_pos = line.startPoint;
			}
			else if (_pos.x > line.endPoint.x)
			{
				_pos = line.endPoint;
			}
		}
	} 
	else if(line.direct == vertical)
	{
			/*if (line.startPoint.y < line.endPoint.y && _pos == line.startPoint && megamanPos.y > line.startPoint.y)
			{
				isMoving = true;
				endPoint = line.endPoint;
			} 
			else if(line.startPoint.y > line.endPoint.y && _pos == line.startPoint && megamanPos.y < line.endPoint.y)
			{
				isMoving = true;
				endPoint = line.endPoint;
			}
			else if (_pos == line.endPoint && megamanPos.y < line.startPoint.y)
			{
				isMoving = true;
				endPoint = line.startPoint;
			}*/
		if (line.startPoint.y < line.endPoint.y)		// neu la huong di len
		{
			
			if (_pos == line.startPoint && megamanPos.y > line.startPoint.y)
			{
				isMoving = true;
				endPoint = line.endPoint;
			} 
			else if(_pos == line.endPoint && megamanPos.y < line.startPoint.y)
			{
				isMoving = true;
				endPoint = line.startPoint;
			}
		} 
		else                                                // neu la huong di xuong
		{
			if (_pos == line.startPoint && megamanPos.y < line.endPoint.y)
			{
				isMoving = true;
				endPoint = line.endPoint;
			} 
			else if(_pos == line.endPoint && megamanPos.y > line.endPoint.y)
			{
				isMoving = true;
				endPoint = line.startPoint;
			}
		}
	}
}

D3DXVECTOR3 Camera::GetPointTransform(int x, int y)
{
	_MatrixTransform._41 = -_pos.x;
	_MatrixTransform._42 = _pos.y;

	D3DXVECTOR3 pos(x, y, 0);
	D3DXVECTOR4 v_result;

	D3DXVec3Transform(&v_result, &pos, &_MatrixTransform);

	return D3DXVECTOR3(v_result.x, v_result.y, 0);
}

void Camera::Transform(D3DXVECTOR2* position)
{
	D3DXVECTOR4 outTransform;

	// Transform theo ma trận tranform
	D3DXVec3Transform(&outTransform, &D3DXVECTOR3(position->x, position->y, 0), &_MatrixTransform);

	position->x = floor( outTransform.x);
	position->y =floor( outTransform.y);

}

RECT Camera::getViewPort()
{
	RECT rect;
	rect.left = _pos.x ;
	rect.top = _pos.y;
	rect.right = rect.left + SCREEN_WIDTH;
	rect.bottom = rect.top - SCREEN_HEIGHT;

	return rect;

}