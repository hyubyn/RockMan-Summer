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
		megaman->Initlize();

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

		machine =  new CEnemyMachine();
		machine->_position = D3DXVECTOR2(150,150);
		machine->_id = 7;
		machine->_size = D3DXVECTOR2(16, 8);
		machine->Initlize();

		machineauto = new  CEnemyMachineAuto(34,1, ResourceManager::GetSprite(ID_SPRITE_ENEMY_MACHINE_AUTO_BLUE), ResourceManager::GetSprite(ID_SPRITE_EXPLODING_EFFECT_BASE), ID_SPRITE_BULLET_BLUE_COLOR, ENEMYMACHINEAUTO_ORIENTATION::BOTTOM,
					D3DXVECTOR2(0 / 1000.0f, 0),
					D3DXVECTOR2((float)80, (float)10), DAME_ENEMY_MACHINE_AUTO, BLOOD_ENEMY_MACHINE_AUTO, 1 * SCORE_DEFAULT);
		machineauto->_size = D3DXVECTOR2((float)16, (float)16);
		machineauto->Initlize();
	

		eneNinja =  new CEnemyNinja();
		eneNinja->_position = D3DXVECTOR2(150,150);
		eneNinja->_id = 7;
		eneNinja->_size = D3DXVECTOR2(26, 24);
		eneNinja->Initlize();
}

void CPlayState::UpdateKeyboard(MKeyboard* input)
{
	
}

void CPlayState::Update(CTimer* gameTime)
{
	megaman->Update(gameTime);
	fish->Update(gameTime,megaman);
	machine->Update(gameTime,megaman);
	machineauto->Update(gameTime,megaman);
	eneNinja->Update(gameTime,megaman);
}

void CPlayState::Draw(CTimer* gameTime, MGraphic* graphics)
{
	tileManager->RenderTile(graphics,this->_camera);
	
	map->Render(graphics,this->_camera);
	
	tileManager->RenderTile(graphics,this->_camera);

	fish->Render(gameTime,graphics);

	machine->Render(gameTime,graphics);

	machineauto->Render(gameTime,graphics);

	eneNinja->Render(gameTime,graphics);

	megaman->Render(gameTime, graphics);



}

CPlayState::~CPlayState(void)
{
}
