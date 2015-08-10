#include "Tile.h"

CTile::CTile(vector<vector<int>> matrix, CTexture bkg, int total, int rowcount, int columncount)
{
	_countRow = rowcount;
	_countColumn = columncount;
	_totalTile = total;
	_textureBkg = bkg;
	for (int i = 0; i < _countRow; i++)
	{
		_tileMatrix.push_back(matrix.at(i));
	}
}

CTile::CTile(MGraphic* graphic)
{
	this->_graphic = graphic;
}

CTile::CTile(void)
{
}


CTile::~CTile(void)
{
}

void CTile::RenderTile(MGraphic* graphics, Camera* cam)
{
	RECT viewport = cam->getViewPort();
	int startRow = floor(viewport.bottom / TILE_SIZE);
	int endRow = floor(viewport.top / TILE_SIZE) + 1;
	int startColumn = floor(viewport.left / TILE_SIZE);
	int endColumn = floor(viewport.right / TILE_SIZE) + 1;

	int bitmapColumn = (int)sqrt((double)_totalTile) + 1;

	if (startColumn < 0)
		startColumn = 0;
	if (startRow < 0)
		startRow = 0;
	if (endColumn > _countColumn)
		endColumn = _countColumn;
	if (endRow > _countRow)
		endRow = _countRow;
	D3DXVECTOR2 startDrawPos = D3DXVECTOR2(startColumn*TILE_SIZE + TILE_SIZE / 2, endRow*TILE_SIZE - TILE_SIZE / 2);
	for (int i = endRow; i > startRow; i--)
	{
		for (int j = startColumn; j < endColumn; j++)
		{
			RECT desRect;
			desRect.top = (_tileMatrix[_countRow - i][j] / bitmapColumn)* TILE_SIZE;
			desRect.left = (_tileMatrix[_countRow - i][j] % bitmapColumn)*TILE_SIZE;
			desRect.right = desRect.left + TILE_SIZE;
			desRect.bottom = desRect.top + TILE_SIZE;

			graphics->DrawTile(_textureBkg.GetTexture(), desRect, startDrawPos, true, D3DXVECTOR2(1.0f, 1.0f),cam);

			startDrawPos.x += TILE_SIZE;
		}
		startDrawPos.y -= TILE_SIZE;
		startDrawPos.x -= TILE_SIZE*abs(startColumn - endColumn);
	}
}

void CTile::LoadTile(char* file, int id)
{
	ifstream fs;		// Luồng đọc file map
	string line;		// Chuỗi đọc file map
	switch (id)
	{
	case 1:_textureBkg = CTexture("Resources//Resources//Maps//boom_man_stage.bmp", D3DCOLOR_XRGB(255, 255, 255), _graphic->GetDevice()); break;
	case 2:_textureBkg = CTexture("Resources//Resources//Maps//cut_man_stage.bmp", D3DCOLOR_XRGB(255, 255, 255), _graphic->GetDevice());break;
	case 3: _textureBkg = CTexture("Resources//Resources//Maps//guts_man_stage.bmp", D3DCOLOR_XRGB(255, 255, 255), _graphic->GetDevice());break;
	default:
		break;
	}
	
	// Mở file và đọc, nếu không được thì out
	fs.open(file, ios::in);
	if (!fs.is_open())
	{
		OutputDebugString("Can not open map file");
		return;
	}

	istringstream iss;								

#pragma endregion

#pragma region Tiến hành đọc dữ liệu từ file .txt

#pragma region Lấy thông tin ma trận tile

	getline(fs, line);
	if (line.compare("#Tile_Matrix") == 0)
	{
		getline(fs, line);								// Bỏ qua dòng "Total_Row	Total_Column	Total_Tile"
		getline(fs, line);
		iss.clear();
		iss.str(line);
		iss >> _countRow >> _countColumn >> _totalTile;	// Đẩy giá trị tổng số dòng, cột, tổng số tile vào biến
		getline(fs, line);								// Bỏ qua dòng "#Tile_Matrix_Value"

		// Tạo mảng hai chiều lưu ma trận tile
		for (int i = 0; i < _countRow; i++)
		{
			vector<int> row;
			row.resize(_countColumn);
			_tileMatrix.push_back(row);
		}

		// Tiến hành đọc dữ liệu
		for (int i = 0; i < _countRow; i++)
		{
			getline(fs, line);
			iss.clear();
			iss.str(line);
			for (int j = 0; j < _countColumn; j++)
				iss >> _tileMatrix[i][j];
		}
		getline(fs, line);					// Bỏ qua dòng "#Tile_Matrix_End"
	}
	fs.close();
#pragma endregion
}