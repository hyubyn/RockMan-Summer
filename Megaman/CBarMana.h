//-----------------------------------------------------------------------------
#ifndef _CBABMANA_H_
#define _CBARMANA_H_

#include "ItemControl.h"
#include "Global.h"
#include "MGraphic.h"
#include "CTextblock.h"
#include "CTexture.h"

class CBarMana : public CItemControl
{
public:
	//-----------------------------------------------------------------------------
	// 	Hàm khởi tạo 
	//-----------------------------------------------------------------------------
	CBarMana();
	CBarMana(D3DXVECTOR2 position, string name);
	~CBarMana();

	//-----------------------------------------------------------------------------
	// 	Khởi tạo tất cả các thành phần của 1 đối tượng với các giá trí đã có
	//	
	//	Trả về 0 nếu lối hoặc 1 nếu thành công
	//-----------------------------------------------------------------------------
	int Initlize(MGraphic* gra) override;

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
	// Set giá trị mana
	//-----------------------------------------------------------------------------
	void SetMana(int mana);

	void IsDraw(boolean isdraw);
private:
	RECT _boundingBG;
	RECT _boundingMana;
	D3DXVECTOR2 _position;

	int _mana;// giá trị chính của mana chạy từ 0->20 
	int _maxMana;
	CTexture _textureMana;
	CTexture _textureBG;
	CTextblock _text;
	boolean _isDraw;

	

};
#endif //!_CPROGRESSBAR_H_

