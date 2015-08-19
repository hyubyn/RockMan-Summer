#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_
#include "Node.h"
#include <fstream>
#include <sstream>
using namespace std;
class CQuadTree
{
	vector<CGameObject*> _listAllGameObject;
	map<INT32,CNode*> _mapNode;
	int _objectCount;
	int _nodeCount;
public:
	vector<CGameObject*> _listObjectOnScreen;
	CQuadTree(void);
	CNode* _nodeRoot;
	void LoadMap(int mapId);
	void BuildTree(CNode* root);
	void ClipCamera(CNode* root, RECT viewPort);
	//void Render(MGraphic* graphic, Camera* cam);
	int nodeCountForDebug;

	~CQuadTree(void);
};

#endif