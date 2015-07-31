#include "PlayState.h"


CPlayState::CPlayState(char *pathmap, MGraphic* gra, LPDIRECT3DDEVICE9 d3ddev, MKeyboard* input)
{
		this->_graphic = gra;
		content = new MContent(gra->GetDevice());

		megaman = new Megaman();
		megaman->Init(content);

		map = new Map();
		map->Init(content);

		tileManager = new CTile(gra);
		tileManager->LoadTile(pathmap);

		this->SetInput(input);

}

void CPlayState::UpdateKeyboard(MKeyboard* input)
{
	
}

void CPlayState::Update(CTimer* gameTime)
{
	megaman->Update(gameTime->GetTime(),this->_input,this->_camera,map->listGameObject);
}

void CPlayState::Draw(CTimer* gameTime, MGraphic* graphics)
{
	tileManager->RenderTile(graphics,this->_camera);
	
	map->Render(graphics,this->_camera);
	
	tileManager->RenderTile(graphics,this->_camera);

	megaman->Render(graphics,this->_camera);
}

CPlayState::~CPlayState(void)
{
}
