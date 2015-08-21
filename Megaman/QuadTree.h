#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_
#include "Node.h"
#include "Global.h"
#include "GameObjectFactory.h"
#include <fstream>
#include <sstream>
using namespace std;
class CQuadTree
{
	vector<CGameObject*> _listAllGameObject;
	map<INT32,CNode*> _mapNode;
	int _nodeCount;
	int _objectCount;
public:
	vector<CGameObject*> _listObjectOnScreen;
	CQuadTree(void);
	CNode* _nodeRoot;
	void LoadMap(int mapId);
	void BuildTree(CNode* root);
	void ClipCamera(CNode* root, RECT viewPort);
	void Render(CTimer* gameTime, MGraphic* graphics);
	void Update(CTimer* gameTime, Megaman* rockman);
	int nodeCountForDebug;

	~CQuadTree(void);
};

#endif