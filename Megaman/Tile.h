﻿#pragma once
#include "Global.h"
#include "Camera.h"
#include "MGraphic.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include "CTexture.h"
#include <vector>
using namespace std;
class CTile
{
private:
	int _totalTile;
	int _countColumn;
	int _countRow;
	CTexture _textureBkg;
	vector<vector<int>>		_tileMatrix;	// Ma trận lưu các tile background
	MGraphic* _graphic;
public:
	CTile(void);
	// ham load demo
	CTile(MGraphic* graphic);
	void LoadTile(char* file);
	CTile(vector<vector<int>>, CTexture, int, int, int);
	void RenderTile(MGraphic*, Camera*);
	~CTile(void);
};

