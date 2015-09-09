#include "QuadTree.h"


CQuadTree::CQuadTree(void)
{
	_nodeRoot = NULL;
	nodeCountForDebug = 1;
	_prepareForBoss = 0;
	_isBossDied = false;
}


CQuadTree::~CQuadTree(void)
{
}

void CQuadTree::LoadMap(int mapId, Camera *cam)
{
	wchar_t* state = nullptr;
	switch (mapId)
	{
	case 1: state = L"Resources//Resources//Maps//Quad_Boom.txt";break;
	case 2: state = L"Resources//Resources//Maps//Quad_Cut.txt";break;
	case 3: state = L"Resources//Resources//Maps//Quad_Guts.txt";break;

	default:
		break;
	}
	ifstream fs;		// Luồng đọc file path
	string line;		// Chuỗi đọc file path
	fs.open(state, ios::in);
	if (!fs.is_open())
	{
		OutputDebugString("Can not open map file");
		return;
	}
	istringstream iss;	
	getline(fs, line);								// bo qua dong #objects
	getline(fs, line);								// bo qua dong objcount
	getline(fs, line);
	iss.clear();
	iss.str(line);
	iss>>_objectCount;
	getline(fs, line);								// bo qua dong ObjID	TypeID	PosX	PosY	Width	Height	PosXCollide	PosYCollide	WidthCollide	HeightCollide
	int id, type = 0, x, y, width, height, xCollide, yCollide, posXCollide, posYCollide; 
	for (int i = 0; i < _objectCount; ++i)
	{
		if (i == _objectCount - 1)
		{
			int a = 0;
		}
		
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss>>id>>type>>x>>y>>width>>height>>xCollide>>yCollide>>posXCollide>>posYCollide;
		if (type == 29)
		{
			
			int b = 1;
		}
		CGameObjectFactory::GetInstance()->cam = cam;
		CGameObject * object = CGameObjectFactory::GetInstance()->CreateObject(id, type, x, y, width, height, xCollide, yCollide, posXCollide, posYCollide);
		if (object != NULL)
		{
			_listAllGameObject.push_back(object);
		}
		
	}
	getline(fs, line);		// bo qua dong #objectend
	getline(fs, line);		// bo qua dong #QuadTree Collision
	getline(fs, line);		// bo qua dong #Nodecount
	getline(fs, line);
	iss.clear();
	iss.str(line);
	iss>>_nodeCount;
	INT32 nodeId;
	int nodeX, nodeY, nodeWidth, nodeHeight, objectCount;
	getline(fs, line);	// bo qua dong #NodeID ....
	int sumObjectInNode = 0;
	for (int i = 0; i < _nodeCount; ++i)
	{
		vector<int> listId;
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss>>nodeId>>nodeX>>nodeY>>nodeWidth>>nodeHeight>>objectCount;
		sumObjectInNode += objectCount;
		for (int i = 0; i < objectCount; i++)
		{
			int objectId;
			iss>>objectId;
			listId.push_back(objectId);
		}
		CNode* node = new CNode(nodeId,nodeX,nodeY,nodeWidth,nodeHeight,objectCount,listId);
		_mapNode[nodeId] = node;
	}
	fs.close();
	_nodeRoot = _mapNode[0];
	BuildTree(_nodeRoot);
}

void CQuadTree::BuildTree(CNode* root)
{
	// tao node la tu node cha dua tren hash map da load tu file map len

	for(map<INT32,CNode*>::iterator i = _mapNode.begin();i != _mapNode.end();++i)
	{
		if((*i).first == root->_nodeId*4 + 1)
		{

			int width = root->_width / 2;
			int height = root->_height / 2;
			root->_lt = new CNode(root->_nodeId* 4 + 1, root->_x, root->_y, root->_width, root->_height);
			root->_rt = new CNode(root->_nodeId* 4 + 2, root->_x, root->_y, root->_width, root->_height);
			root->_rb = new CNode(root->_nodeId* 4 + 3, root->_x, root->_y, root->_width, root->_height);
			root->_lb = new CNode(root->_nodeId* 4 + 4, root->_x, root->_y, root->_width, root->_height);
			BuildTree(root->_lt);
			BuildTree(root->_lb);
			BuildTree(root->_rt);
			BuildTree(root->_rb);
			nodeCountForDebug += 4;
		}
	}

	// add ObjectID va Object cho Node hien tai
	for(map<INT32,CNode*>::iterator i = _mapNode.begin();i != _mapNode.end();++i)
	{
		if((*i).first == root->_nodeId)
		{
			root->_objectCount = (*i).second->_objectCount;
			for (int j = 0; j < root->_objectCount; ++j)
			{
				root->_listObjectId.push_back((*i).second->_listObjectId.at(j));
			}
			for (int k = 0; k < _listAllGameObject.size(); ++k)
			{
				for (int l = 0; l < root->_objectCount; ++l)
				{
					if (_listAllGameObject.at(k)->_id == root->_listObjectId.at(l))
					{
						root->AddObject(_listAllGameObject.at(k));
					}
				}
				
			}
		}
	}
}

void CQuadTree::ClipCamera(CNode* root, RECT viewPort)
{

	if (root->ClipCamera(viewPort) == 1)
	{
		if (root->_lt != NULL)
		{
			ClipCamera(root->_lt,viewPort);
			ClipCamera(root->_lb,viewPort);
			ClipCamera(root->_rt,viewPort);
			ClipCamera(root->_rb,viewPort);
		}
		else
		{
			try
			{
				viewPort.right += 150;
				
				for (int i = 0; i < root->_objectCount; i++)
				{
					if (root->_listGameObject.at(i)->GetCollideRegion().IntersecWith(viewPort) || root->_listGameObject.at(i)->_position.y < viewPort.bottom)
					{
					_listObjectOnScreen[root->_listGameObject.at(i)->_id] = root->_listGameObject.at(i);

					}
				}				
			}
			catch(std::out_of_range e)
			{
				int a = 0;
			}
			
			
		}
		
	}
	else
	{
		for (int j = 0; j < root->_listGameObject.size(); ++j)
		{
			for(map<int,CGameObject*>::iterator i = _listObjectOnScreen.begin();i != _listObjectOnScreen.end();++i)
			{
				
				if ((*i).second->_id == root->_listGameObject.at(j)->_id)
				{
					map<int, CGameObject*>::iterator toErase = i;
					_listObjectOnScreen.erase(toErase);
				}
			}
		}
		
	}
}

void CQuadTree::Render(CTimer* gameTime, MGraphic* graphics)
{
	// objects = tree->getObjects(camera);

	// for (int i=0;i< all objects) 
		//re

	// objects->delete();

	
	//for (int i = 0; i < _groundObjs.size(); ++i)
	//{
	//	_groundObjs.at(i)->Render(gameTime, graphics);
	//}

	//for (int i = 0; i < _elevators.size(); ++i)
	//{
	//	_elevators.at(i)->Render(gameTime, graphics);
	//}

	//for (int i = 0; i <  _enemies.size(); ++i)
	//{
	//	_enemies.at(i)->Render(gameTime, graphics);
	//}

	//for (int i = 0; i < _items.size(); i++)
	//{
	//	_items.at(i)->Render(gameTime, graphics);
	//}
}

void CQuadTree::Update(CTimer* gameTime, Megaman* _rockman, Camera* cam)
{
	
}