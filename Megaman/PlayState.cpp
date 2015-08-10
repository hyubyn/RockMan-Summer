#include "PlayState.h"


CPlayState::CPlayState(char *pathmap, MGraphic* gra, LPDIRECT3DDEVICE9 d3ddev, MKeyboard* input, Camera* cam, int id)
{
		cam->LoadCameraPath(id);
		this->_camera = cam;
		this->_graphic = gra;
		_graphic->GetCam(cam);
		_graphic->SetDevice(d3ddev);
		content = new MContent(gra->GetDevice());

		megaman = new Megaman();
		megaman->Init(content);

		map = new Map();
		map->Init(content);

		tileManager = new CTile(gra);
		tileManager->LoadTile(pathmap, id);

		this->SetInput(input);
		//enemy
		fish = new CEnemyFish(cam->_pos.y - 112);
		fish->_position = D3DXVECTOR2(200, cam->_pos.y - 112);
		fish->_id = 4;
		fish->_size = D3DXVECTOR2(16,16);
		fish->Initlize();
}

void CPlayState::UpdateKeyboard(MKeyboard* input)
{
	
}

void CPlayState::Update(CTimer* gameTime)
{
	megaman->Update(gameTime->GetTime(),this->_input,this->_camera,map->listGameObject);

	fish->Update(gameTime,megaman);
}

void CPlayState::Draw(CTimer* gameTime, MGraphic* graphics)
{
	tileManager->RenderTile(graphics,this->_camera);
	
	map->Render(graphics,this->_camera);
	
	tileManager->RenderTile(graphics,this->_camera);

	fish->Render(gameTime,graphics);

	megaman->Render(graphics,this->_camera);


}

CPlayState::~CPlayState(void)
{
}
