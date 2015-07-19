#include "Collision.h"


CCollision::CCollision()
{
}

CCollision::~CCollision()
{

}

Box CCollision::GetSweptBroadphaseBox(Box b, float t)
{
	Box broadphaseBox;
	broadphaseBox._x = b._vx > 0 ? b._x : b._x + b._vx * t;
	broadphaseBox._y = b._vy < 0 ? b._y : b._y + b._vy * t;
	broadphaseBox._width = b._vx > 0 ? b._vx * t + b._width : b._width - b._vx * t;
	broadphaseBox._height = b._vy > 0 ? b._vy * t + b._height : b._height - b._vy * t;

	return broadphaseBox;
}

bool CCollision::AABBCheck(Box b1, Box b2)
{
	return !(b1._x + b1._width < b2._x || b1._x > b2._x + b2._width || b1._y < b2._y - b2._height || b1._y - b1._height > b2._y);
}

float CCollision::SweepAABB(Box box1, Box box2, CDirection &normalX, CDirection &normalY, float frameTime)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// Xác định các khoảng cách bắt đầu và kết thúc va chạm theo hai chiều x, y
	if (box1._vx > 0.0f)
	{
		xInvEntry = box2._x - (box1._x + box1._width);
		xInvExit = (box2._x + box2._width) - box1._x;
	}
	else
	{
		xInvEntry = (box2._x + box2._width) - box1._x;
		xInvExit = box2._x - (box1._x + box1._width);
	}

	if (box1._vy > 0.0f)
	{
		yInvEntry = (box2._y - box2._height) - box1._y;
		yInvExit = box2._y - (box1._y - box1._height);
	}
	else
	{
		yInvEntry = box2._y - (box1._y - box1._height);
		yInvExit = (box2._y - box2._height) - box1._y;
	}

	// Tính thời gian bắt đầu và kết thúc va chạm theo hai chiều x, y
	float xEntry, xExit;
	float yEntry, yExit;

	if (box1._vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1._vx;
		xExit = xInvExit / box1._vx;
	}

	if (box1._vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / box1._vy;
		yExit = yInvExit / box1._vy;
	}

	// Tìm ra khoảng thời gian bắt đầu và kết thúc va chạm tổng hợp
	float entryTime, exitTime;

	entryTime = __max(xEntry, yEntry);
	exitTime = __min(xExit, yExit);

#pragma region Xét va chạm với các trường hợp còn lại
	// Nếu không có va chạm trong frameTime này thì trả về false
	if (entryTime > exitTime || xEntry<0.0f&&yEntry<0.0f || xEntry>frameTime || yEntry>frameTime)
	{
		// Mặc định không va chạm theo hai hướng
		normalX = CDirection::NONE_DIRECT;
		normalY = CDirection::NONE_DIRECT;

		if (box1.IsIntersect(box2))
		{
			// Nếu 2 box va chạm lẫn nhau thì có thể hai box này đã dính nhau
			if (fabsf(box1._y - box1._height - box2._y) <= 2.0f
				&& !(box1._x + box1._width <= box2._x || box1._x >= box2._x + box2._width))
				normalY = CDirection::ON_DOWN;

			else if (fabsf(box1._y - (box2._y - box2._height)) <= 2.0f
				&& !(box1._x + box1._width <= box2._x || box1._x >= box2._x + box2._width))
				normalY = CDirection::ON_UP;

			else if (fabsf(box1._x + box1._width - box2._x) <= 2.0f
				&& !(box1._y - box1._height >= box2._y || box1._y <= box2._y - box2._height))
				normalX = CDirection::ON_RIGHT;

			else if (fabsf(box1._x - (box2._x + box2._width)) <= 2.0f
				&& !(box1._y - box1._height >= box2._y || box1._y <= box2._y - box2._height))
				normalX = CDirection::ON_LEFT;

			else if (!(box1._y - box1._height >= box2._y
				|| box1._y <= box2._y - box2._height
				|| box1._x + box1._width <= box2._x
				|| box1._x >= box2._x + box2._width))
				normalX = normalY = CDirection::INSIDE;
		}
		return 0;
	}
#pragma  endregion
#pragma region Nếu có va chạm xảy ra
	else
	{
		if (xEntry > yEntry)
		{
			if (box1._vx > 0.0f) // Nếu va chạm từ trái sang phải
			{
				if (!(box1._y - box1._height >= box2._y || box1._y <= box2._y - box2._height))
				{
					normalX = CDirection::ON_RIGHT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1._y - box1._height - box2._y) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf(box1._y - (box2._y - box2._height) <= 2.0f))
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ phải sang trái
			{
				if (!(box1._y - box1._height >= box2._y || box1._y <= box2._y - box2._height))
				{
					normalX = CDirection::ON_LEFT;
					normalY = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1._y - box1._height - box2._y) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_DOWN;
						entryTime = 0.0f;
					}
					else if (fabsf(box1._y - (box2._y - box2._height)) <= 2.0f)
					{
						normalX = CDirection::NONE_DIRECT;
						normalY = CDirection::ON_UP;
						entryTime = 0.0f;
					}
				}
			}
		}
		else
		{
			if (box1._vy > 0.0f) // Nếu va chạm từ dưới lên
			{
				if (!(box1._x + box1._width <= box2._x || box1._x >= box2._x + box2._width))
				{
					normalY = CDirection::ON_UP;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1._x + box1._width - box2._x) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf(box1._x - (box2._x + box2._width)) < 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
			else // Nếu va chạm từ trên xuống
			{
				if (!(box1._x + box1._width <= box2._x || box1._x >= box2._x + box2._width))
				{
					normalY = CDirection::ON_DOWN;
					normalX = CDirection::NONE_DIRECT;
				}
				else
				{
					if (fabsf(box1._x + box1._width - box2._x) <= 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_RIGHT;
						entryTime = 0.0f;
					}
					else if (fabsf(box1._x - (box2._x + box2._width)) < 2.0f)
					{
						normalY = CDirection::NONE_DIRECT;
						normalX = CDirection::ON_LEFT;
						entryTime = 0.0f;
					}
				}
			}
		}
		return entryTime;
#pragma endregion
	}

}