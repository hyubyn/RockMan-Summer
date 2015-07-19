#include <limits>

#ifndef _COLLISION_H_
#define _COLLISION_H_

// Struct Box dùng để bao đối tượng lại để xét va chạm.
struct Box
{
	float x, y;             /* Vị trí của box */
	float width, height;    /* Chiều dài và chiều cao của box */
	float vX, vY;           /* Vận tốc của box */

	//Phương thức khởi tạo của lớp box
	Box(){

	}

	Box(float x, float y, float w, float h, float vx, float vy)
	{
		this->x = x;
		this->y = y;
		this->width = w;
		this->height = h;
		this->vX = vx;
		this->vY = vy;
	}

	bool IsIntersect(Box box)
	{
		bool result = true;
		if (x + width < box.x
			||box.x + box.width < x
			||y - height > box.y
			||box.y - box.height > y)
			result = false;
		return result;
	}
};

	//Lớp CCollision hỗ trợ các phương thức để xét va chạm giữa 2
	//đối tượng trong game theo thuật toán Sweep AABB.
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
	static float SweepAABB(Box b1, Box b2, float& normalx,float& normaly, float timeFrame);
};

#endif // _COLLISION_H_