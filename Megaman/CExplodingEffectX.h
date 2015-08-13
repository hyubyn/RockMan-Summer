﻿//-----------------------------------------------------------------------------"
// File: CExplodingEffectX.h
//
// Desc: Định nghĩa lớp CExplodingEffectX tạo hiệu ứng nổ vòng
//
//-----------------------------------------------------------------------------
#ifndef _CEXPLODING_EFFECT_X_H_
#define _CEXPLODING_EFFECT_X_H_

#include "ExplodingEffect.h"

class CExplodingEffectX :public CExplodingEffect
{
public:
	//-----------------------------------------------------------------------------
	// Phương thức khởi tạo màn hình PlayScreen với số màn tương ứng
	//-----------------------------------------------------------------------------

	CExplodingEffectX(D3DXVECTOR2 position, CSprite sprite, bool explodeBig=true);
	~CExplodingEffectX();

	//-----------------------------------------------------------------------------
	// Phương thức cập nhật màn hình theo thời gian thực
	//-----------------------------------------------------------------------------
	void Update(CTimer* gameTime) override;

	//-----------------------------------------------------------------------------
	// Phương thức vẽ màn hình và các thành phần con bên trong
	//-----------------------------------------------------------------------------
	void Render(CTimer* gameTime, MGraphic* graphics) override;

private:
	D3DXVECTOR2 _v, _a;
	float	_distance1, _distance2;
	bool	_isExplodeBig;
};

#endif //!_CEXPLODING_EFFECT_X_H_