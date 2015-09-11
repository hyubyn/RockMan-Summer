#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_
#include "Node.h"
#include "Global.h"
#include "GameObjectFactory.h"
#include "Camera.h"
#include <fstream>
#include <sstream>
using namespace std;
class CQuadTree
{
	
	map<INT32,CNode*> _mapNode;
	int _nodeCount;
	int _objectCount;
public:
	map<int, CGameObject*> _listObjectOnScreen;
	vector<CGameObject*> _listAllGameObject;
	int _prepareForBoss;
	CSprite		_spriteIntroBoss;
	bool		_isBossDied;				// Kiểm tra boss có chết hay chưa
	CQuadTree(void);
	CNode* _nodeRoot;
	void LoadMap(int mapId, Camera* cam);
	void BuildTree(CNode* root);
	void ClipCamera(CNode* root, RECT viewPort);
	void Render(CTimer* gameTime, MGraphic* graphics);
	void Update(CTimer* gameTime, Megaman* rockman,Camera* cam );
	int nodeCountForDebug;
	vector<CNode*> listNodeForDebug;
	~CQuadTree(void);
};

#endif