#include <limits>

#ifndef _COLLISION_H_
#define _COLLISION_H_

// Struct Box dùng để bao đối tượng lại để xét va chạm.
struct Box
{
	float _vx, _vy;	// Vận tốc chuyển động các vật thể
	float _x, _y;	// Tọa độ các đối tượng trong hệ quy chiếu
	float _width, _height;	// Kích thước của vật thể

	//Phương thức khởi tạo của lớp box
	Box(){

	}

	Box(float x, float y, float w, float h, float vx, float vy)
	{
		this->_x = x;
		this->_y = y;
		this->_width = w;
		this->_height = h;
		this->_vx = vx;
		this->_vy = vy;
	}

	bool IsIntersect(Box box)
	{
		bool result = true;
		if (_x + _width < box._x
			|| box._x + box._width < _x
			|| _y - _height > box._y
			|| box._y - box._height > _y)
			result = false;
		return result;
	}
};

	//Lớp CCollision hỗ trợ các phương thức để xét va chạm giữa 2
	//đối tượng trong game theo thuật toán Sweep AABB.
enum CDirection
{
	// Hướng lên
	ON_UP = 101,
	// Hướng xuống
	ON_DOWN = 102,
	// Hướng bên phải
	ON_RIGHT = 103,
	// Hướng bên trái
	ON_LEFT = 104,
	NONE_DIRECT = 105,
	// Hai vật nằm lồng trong nhau
	INSIDE = 106
};

class CCollision
{
public:
	CCollision();
	~CCollision();

	/*M+==================================================================
	Method:	    CCollision::GetSwpetBroadphaseBox

	Summary:	Phương thức tạo ra Broadphase box.
	==================================================================-M*/
	static Box GetSweptBroadphaseBox(Box b, float t);

	/*M+==================================================================
	Method:	    CCollision::AABBCheck

	Summary:	Phương thức kiểm tra xem 2 đối tượng có thể xảy ra va chạm 
				hay không trước khi kiểm tra bằng SweepAABB. Tăng hiệu xuất
				của chương trình khi có nhiều đối tượng.
	==================================================================-M*/
	static bool AABBCheck(Box b1, Box b2);

	/*M+==================================================================
	Method:	    CCollision::SweepAABB

	Summary:	Phương thức kiểm tra xem 2 đối tượng xảy ra va chạm không
				(theo thuật toán Sweep AAABB).

	Args:       b1 - Box của đối tượng di chuyển.
				b2 - Box của đối tượng đứng yên.
				normalx, normaly - Hướng va chạm.
				timeFrame - Thời gian của frame hiện tại.

	Return:     Thời gian xảy ra va chạm nếu có va chạm hoặc
	            timeFrame nếu không có va chạm.
	==================================================================-M*/
	static float SweepAABB(Box box1, Box box2, CDirection &normalX, CDirection &normalY, float frameTime);
};

#endif // _COLLISION_H_