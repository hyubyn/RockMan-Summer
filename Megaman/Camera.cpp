#include "Camera.h"
#include "Global.h"

Camera::Camera()
{
	_pos.x = 0;
	_pos.y = SCREEN_HEIGHT;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	D3DXMatrixIdentity(&_MatrixTransform);
	_MatrixTransform._22 = -1;

}


Camera::~Camera()
{
}

void Camera::Update(D3DXVECTOR2 megamanPosition)
{
	_pos.x = megamanPosition.x - width / 2;
	if (_pos.x < 0)
		_pos.x = 0;
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