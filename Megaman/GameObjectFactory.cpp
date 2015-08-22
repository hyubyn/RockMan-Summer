#include "GameObjectFactory.h"


CGameObjectFactory::CGameObjectFactory(void)
{
}


CGameObjectFactory::~CGameObjectFactory(void)
{
}

CGameObject* CGameObjectFactory::CreateObject(int objID, int typeID, int posX, int posY,int width,int height,int posXCollide,int posYCollide,int widthCollide,int heightCollide)
{
	CGameObject* obj = NULL;
	switch (typeID)
	{
	case ID_ENEMY_BALL:
		obj = new  CEnemyBall(objID, typeID,
			ResourceManager::GetSprite(ID_SPRITE_ENEMY_BALL),
			ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			50.f / 1000.0f,
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_BALL, BLOOD_ENEMY_BALL, 4 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_BOOM_BLUE:
		obj = new  CEnemyBoom(objID, typeID,
			ResourceManager::GetSprite(ID_SPRITE_ENEMY_BOOM_BLUE),
			ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			100.f / 1000.0f,
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_BOOM, BLOOD_ENEMY_BOOM, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;

	case ID_ENEMY_EYE_RED_UP:
		obj = new  CEnemyEye(1);
		break;
	case ID_ENEMY_EYE_RED_RIGHT:
		obj = new  CEnemyEye(0);
		break;
	case ID_ENEMY_FISH_ORANGE:
		obj = new  CEnemyFish(posY);
		break;
	case ID_ENEMY_INK_RED:
		obj = new  CEnemyInk(0);
		break;
	case ID_ENEMY_MACHINE_AUTO_BLUE_TOP:
		obj = new  CEnemyMachineAuto(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_MACHINE_AUTO_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ID_SPRITE_BULLET_BLUE_COLOR, ENEMYMACHINEAUTO_ORIENTATION::TOP,
			D3DXVECTOR2(0 / 1000.0f, 0),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_MACHINE_AUTO, BLOOD_ENEMY_MACHINE_AUTO, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_MACHINE_AUTO_BLUE_BOTTOM:
		obj = new  CEnemyMachineAuto(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_MACHINE_AUTO_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ID_SPRITE_BULLET_BLUE_COLOR, ENEMYMACHINEAUTO_ORIENTATION::BOTTOM,
			D3DXVECTOR2(0 / 1000.0f, 0),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_MACHINE_AUTO, BLOOD_ENEMY_MACHINE_AUTO, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide); 
		return obj;
		break;
	case ID_ENEMY_MACHINE_ORANGE:
		obj = new  CEnemyMachine();
		break;
	case ID_ENEMY_NINJA_GREEN:
		obj = new  CEnemyNinja();
		break;
	case ID_ENEMY_CUT:

		break;
	case ID_ENEMY_INK_BLUE:
		obj = new  CEnemyInk(1);
		break;
	case ID_ENEMY_MACHINE_AUTO_ORGANGE_TOP:
		obj = new  CEnemyMachineAuto(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_MACHINE_AUTO_ORGANGE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ID_SPRITE_BULLET_ORANGE_COLOR, ENEMYMACHINEAUTO_ORIENTATION::TOP,
			D3DXVECTOR2(0 / 1000.0f, 0),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_MACHINE_AUTO, BLOOD_ENEMY_MACHINE_AUTO, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_MACHINE_AUTO_ORGANGE_BOTTOM:
		obj = new  CEnemyMachineAuto(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_MACHINE_AUTO_ORGANGE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ID_SPRITE_BULLET_ORANGE_COLOR, ENEMYMACHINEAUTO_ORIENTATION::BOTTOM,
			D3DXVECTOR2(0 / 1000.0f, 0),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_MACHINE_AUTO, BLOOD_ENEMY_MACHINE_AUTO, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_WALL_SHOOTER_LEFT:
		obj = new  CEnemyWallShooter(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_WALL_SHOOTER), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ENEMYWALLSHOOTER_ORIENTATION::LEFT,
			D3DXVECTOR2(0 / 1000.0f, 0),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_WALL_SHOOTER, BLOOD_ENEMY_WALL_SHOOTER, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_WALL_SHOOTER_RIGHT:
		obj = new  CEnemyWallShooter(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_WALL_SHOOTER), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ENEMYWALLSHOOTER_ORIENTATION::RIGHT,
			D3DXVECTOR2(0 / 1000.0f, 0),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_WALL_SHOOTER, BLOOD_ENEMY_WALL_SHOOTER, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_ROBOT_RED:
		obj = new  CEnemyRobot(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_ROBOT_RED), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_ROBOT, BLOOD_ENEMY_ROBOT, 7.5 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_BUBBLE_BLUE:
		obj = new  CEnemyBubble(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_BUBBLE_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			D3DXVECTOR2(50.f / 1000.0f, 0.0f / 1000.0f),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_BUBBLE, BLOOD_ENEMY_BUBBLE, 2.5* SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_BUBBLE_GREEN:
		obj = new  CEnemyBubble(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_BUBBLE_GREEN), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			D3DXVECTOR2(50.f / 1000.0f, 0.0f / 1000.0f),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_BUBBLE, BLOOD_ENEMY_BUBBLE, 2.5 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ELEVATOR:
		obj = new  CElevator(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ELEVATOR),
			50.0f / 1000.0f,
			D3DXVECTOR2((float)posX, (float)posY));
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_BLOCK_TROUBLE_OF_ELEVATOR:
		obj = new  CBlock();
		break;
	case ID_ENEMY_HAT:
		obj = new  CEnemyHat();
		break;
	case ID_ENEMY_ROBOT_BLUE:
		obj = new  CEnemyRobot(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_ROBOT_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_ROBOT, BLOOD_ENEMY_ROBOT, 7.5 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
		break;
	case ID_ENEMY_WORKER:
		obj = new  CEnemyWorker(objID, typeID, ResourceManager::GetSprite(ID_SPRITE_ENEMY_WORKER), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE),
			50.0f / 1000.0f,
			D3DXVECTOR2((float)posX, (float)posY), DAME_ENEMY_WORKER, BLOOD_ENEMY_WORKER, 1 * SCORE_DEFAULT);
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		break;
	case ID_BLOCK:
		obj = new  CBlock();
		break;
	case ID_STAIR:
		obj = new  CStair();
		break;
	case ID_DOOR1_CUTMAN:
	case ID_DOOR2_CUTMAN:
		obj = new  CDoor(ResourceManager::GetSprite(ID_SPRITE_DOOR_CUTMAN));
		break;
	case ID_DOOR1_GUTSMAN:
	case ID_DOOR2_GUTSMAN:
		obj = new  CDoor(ResourceManager::GetSprite(ID_SPRITE_DOOR_GUTSMAN));
		break;
	case ID_DOOR1_BOOMMAN:
		obj = new  CDoor(ResourceManager::GetSprite(ID_SPRITE_DOOR1_BOOMMAN));
		break;
	case ID_DOOR2_BOOMMAN:
		obj = new  CDoor(ResourceManager::GetSprite(ID_SPRITE_DOOR2_BOOMMAN));
		break;
	case ID_ITEM_LIFE:
	case ID_ITEM_BLOOD_BIG:
	case ID_ITEM_BLOOD_SMALL:
	case ID_ITEM_MANA_BIG:
	case ID_ITEM_MANA_SMALL:
		obj = new  CItemObject(typeID, D3DXVECTOR2((float)posX, (float)posY), false, true);
		obj->_id = objID;
		obj->_size = D3DXVECTOR2((float)width, (float)height);
		obj->Initlize();
		obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
		return obj;
	case ID_ROCK_IN_GUT_STAGE:
	case ID_ROCK:
		obj = new  CRock();
		break;
	case ID_DIE_ARROW:
		obj = new  CDieArrow();
		break;
	case ID_CUTMAN:
		obj = new  CCutman();
		break;
	/*case ID_GUTSMAN:
		obj = new  CGutsMan();
		break;*/
	case ID_BOOMMAN:
		obj = new  CBoomMan();
		break;
	case ID_ENEMY_SNAPPER:
		obj = new  CEnemySnapper();	
		break;
	 default: return obj;
	}
	obj->_position = D3DXVECTOR2((float)posX, (float)posY);
	obj->_id = objID;
	obj->_typeID = typeID;
	obj->_size = D3DXVECTOR2((float)width, (float)height);
	obj->Initlize();
	obj->SetCollideRegion(posXCollide, posYCollide, widthCollide, heightCollide);
	return obj;
}