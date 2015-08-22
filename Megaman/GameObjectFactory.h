#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "Global.h"
#include "CGameObject.h"
#include "CSingleton.h"

#include "ResourceManager.h"
#include "resource.h"
#include "CTexture.h"
#include "CSprite.h"
#include "CRock.h"
#include "PowerEnergyX.h"
#include "CExplodingEffectManager.h"
#include "CItemObject.h"
#include "DSUtil.h"
#include "Global.h"
#include "CBoomMan.h"
#include "CCutMan.h"
//#include "CGutsMan.h"
#include "CBullet.h"
#include "CDieArrow.h"
#include "CDoor.h"
#include "CEnemy.h"
#include "CEnemyBall.h"
#include "CEnemyBoom.h"
#include "CEnemyBubble.h"
#include "CEnemyEye.h"
#include "CEnemyFish.h"
#include "CEnemyHat.h"
#include "CEnemyInk.h"
#include "CEnemyMachineAuto.h"
#include "CEnemyWallShooter.h"
#include "CEnemyNinja.h"
#include "CEnemyRobot.h"
#include "CEnemyWorker.h"
#include "CElevator.h"
#include "CBlock.h"
#include "CBullet.h"
#include "CEnemyInk.h"
#include "CEnemyEye.h"
#include "CPopup.h"
#include "CEnemySnapper.h"
#include "CElevator.h"
#include "CEnemyMachine.h"
#include "CGameInfo.h"
#include "Asset.h"
#include "CStair.h"
class CGameObjectFactory : public CSingleton<CGameObjectFactory>
{
	friend class CSingleton<CGameObjectFactory>;
public:
	CGameObjectFactory();
public:
	~CGameObjectFactory();
	virtual CGameObject* CreateObject(int objID, int typeID, int posX, int posY,int width,int height,int posXCollide,int posYCollide,int widthCollide,int heightCollide);
};

#endif