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