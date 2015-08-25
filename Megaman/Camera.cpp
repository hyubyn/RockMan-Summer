#include "Camera.h"
#include "Global.h"

Camera::Camera()
{
	
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	isMoving = false;
	D3DXMatrixIdentity(&_MatrixTransform);
	_MatrixTransform._22 = -1;
	_pos.x = 0;
	_pos.y = 256;
	
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
		if (_pos.y < endPoint.y - 3)
		{
			_pos.y += 2;
		}
		else if (_pos.y > endPoint.y + 3)
		{
			_pos.y -= 2;
		}
		else if (_pos.y < endPoint.y)
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
	if (_pos != endMap)
	{
		if (line.direct == horizontal)											// camera di chuyen theo phuong ngang
		{
			if (line.endPoint.x - line.startPoint.x < limitX && _pos.x < line.endPoint.x)	//neu la toa do camera di chuyen qua thi cho camera chay len
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
				if (_pos == line.startPoint && megamanPos.y < line.startPoint.y - SCREEN_HEIGHT)
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

void Camera::SetEndMap(D3DXVECTOR2 point)
{
	this->endMap = point;
}

void Camera::LoadCameraPath(int id)
{
	wchar_t* state = nullptr;
	switch (id)
	{
	case 1: state = L"Resources//Resources//Maps//Boom.txt";break;
	case 2: state = L"Resources//Resources//Maps//Cut.txt";break;
	case 3: state = L"Resources//Resources//Maps//Guts.txt";break;

	default:
		break;
	}
	ifstream fs;		// Luồng đọc file path
	string line;		// Chuỗi đọc file path
	fs.open(state, ios::in);
	if (!fs.is_open())
	{
		OutputDebugString("Can not open map file");
		return;
	}
	int x, y;		// point
	istringstream iss;	
	getline(fs, line);								// Bỏ qua dòng "Total_Row	Total_Column	Total_Tile"
	getline(fs, line);
	iss.clear();
	iss.str(line);
	iss>>count>>limitX;
	for (int i = 0; i < count; i++)
	{
		getline(fs,line);
		iss.clear();
		iss.str(line);
		iss>>x>>y;
		_listPoint.push_back(D3DXVECTOR2(x,y));
	}
	endMap = _listPoint.at(count - 1);										// lay toa do cuoi cung cua camera
	for (int i = 0; i < count - 1; i++)
	{
		_listMoveLine.push_back(MoveLine(_listPoint.at(i), _listPoint.at(i + 1)));
	}
	_pos = _listPoint.at(0);
	_positionBossRoom = _listPoint.at(_listPoint.size() - 1);
	iss.clear();
	fs.close();

}