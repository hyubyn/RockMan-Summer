#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::ReadText(char *FileName)
{
	string String;
	ifstream file;
	list.clear();
	file.open(FileName);
	if (file.is_open())
	{
		getline(file, String);
		dem = atoi(String.c_str());

		int count;
		string a;

		for (int i = 0; i < dem; i++)
		{
			getline(file, String);
			count = String.length();
			for (int j = 0; j < count; j++)
			{
				if (String[j + 1] == ' ')
				{
					a = String.substr(0, j + 1);
					String = String.substr(j + 1, String.length());
					count = String.length();
					j = 0;
					list.push_back(a);
				}
			}
			list.push_back(String);
		}
	}
	file.close();
}

void Map::Init(MContent* content)
{
	this->ReadText("Resources\\Map\\map1.txt");


	for (int i = 0; i < list.size(); i++)
	{
		if (i % 3 == 0)
		{
			if (list.at(i) == "1")
			{
				id = atoi(list.at(i).c_str());
				position.x = (float)atoi(list.at(i + 1).c_str());
				position.y = (float)atoi(list.at(i + 2).c_str());
				width = 16;
				height = 16;
				path = "Resources\\Terrain\\ID1.png";
				StaticGameObject* newland = new StaticGameObject(position, id, width, height, content, path);
				listGameObject.push_back(newland);
				listStaticGameObject.push_back(newland);
			}
		}
	}
}

void Map::Render(MGraphic* graphic, Camera* cam)
{
	D3DXVECTOR3 temppos = cam->GetPointTransform(cam->_pos.x, cam->_pos.y);
	for (int i = 0; i < listGameObject.size(); i++)
	{
		if (listGameObject.at(i)->GetPos().x >= temppos.x - 32 && listGameObject.at(i)->GetPos().x <= temppos.x + SCREEN_WIDTH
			&& listGameObject.at(i)->GetPos().y >= temppos.y && listGameObject.at(i)->GetPos().y < temppos.y + SCREEN_HEIGHT + 32)
		{
			listGameObject.at(i)->Render(graphic, cam);
		}
	}
}