#pragma once
#include "Item.h"
#include "CTexture.h"

class CImageItem: public CItem
{
public:
	CImageItem(void);
	~CImageItem(void);

	//-----------------------------------------------------------------------------
	// 	Khởi tạo tất cả các thành phần của 1 đối tượng với các giá trí đã có
	//	
	//	Trả về 0 nếu lối hoặc 1 nếu thành công
	//-----------------------------------------------------------------------------
	int Initlize(MGraphic* graphic) override;

	//-----------------------------------------------------------------------------
	// 	Cập nhật tất cả các logic của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	//-----------------------------------------------------------------------------
	// 	Vẽ tất cả các thành phần của 1 đối tượng
	//	
	//	+ gameTime	: Thời gian cập nhật hệ thống
	//	+ graphics	: cọ vẽ đối tượng
	//-----------------------------------------------------------------------------
	void Render(CTimer* gameTime,Camera* cam, MGraphic* graphics) override;

	//-----------------------------------------------------------------------------
	// source của bức ảnh
	//-----------------------------------------------------------------------------
	char* _source;	

	
	//-----------------------------------------------------------------------------
	// Màu nền
	//-----------------------------------------------------------------------------
	D3DCOLOR _transparentColor;

	
	//-----------------------------------------------------------------------------
	// bound khung
	//-----------------------------------------------------------------------------
	RECT _boundingRect;
private:

	  // Texture của bức ảnh
	CTexture* _texture;
};

