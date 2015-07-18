#pragma once
#include <d3dx9.h>
#include "MContent.h"
#include "MGraphic.h"
#include "Camera.h"
#include "GameObject.h"
#include "StaticGameObject.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
using namespace std;

#include "Camera.h"
class Map
{
private:
	ifstream file;
public:

	int id;
	D3DXVECTOR2 position;
	int width, height;
	string path;


	vector<string> list;
	int dem;
	

	Map();
	~Map();

	vector<GameObject*> listGameObject;
	vector<StaticGameObject*> listStaticGameObject;

	void ReadText(char* FileName);
	void Init(MContent*);
	void Render(MGraphic*, Camera*);
	
};

