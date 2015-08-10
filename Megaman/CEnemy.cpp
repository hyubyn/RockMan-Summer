#include "CEnemy.h"

CEnemy::CEnemy() :CMoveableObject()
{
	_score = 0;
}
CEnemy::~CEnemy()
{
}

void CEnemy::Update(CTimer* gameTime)
{

}

void CEnemy::Render(CTimer* gameTime, MGraphic* graphic)
{

}

void CEnemy::Update(CTimer* gameTime, Megaman* rockman)
{

}

vector<CBullet*> CEnemy::Fire()
{
	return vector<CBullet*>();
}

CEnemy* CEnemy::ToValue()
{
	return new CEnemy(*this);
}

unsigned int CEnemy::GetScore()
{
	return _score;
}