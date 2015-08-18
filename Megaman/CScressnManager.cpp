#include "CScressnManager.h"

CScreenManager* CScreenManager::_instance = NULL;

CScreenManager::CScreenManager(){

}

CScreenManager::~CScreenManager(){
	_currentScreen->~CScreen();
	_popupScreen->~CScreen();
	_screenItems.clear();
}

CScreenManager* CScreenManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new CScreenManager();

	return _instance;
}

void CScreenManager::SetStartScreen(CScreen* screen)
{
	_currentScreen = screen;
	_popupScreen = NULL;
	_screenItems.push_back(screen);
}

void CScreenManager::Render(CTimer* gameTime, MGraphic* graphics){

	if (_popupScreen != NULL)
	{
		if (_currentScreen != NULL)
		{
			_currentScreen->Draw(gameTime, graphics);
			_popupScreen->Draw(gameTime, graphics);
			
		}
	}
	else
	{
		if (_currentScreen != NULL)
		{
			
			_currentScreen->Draw(gameTime, graphics);
			
		}
	}
}

void CScreenManager::Update(CTimer* gameTime){

	// Nếu không có màn hình popup thì cập nhật màn hình hiện tại đang chạy game
	// Cẩn kiểm tra NULL để xác định biến con trỏ _currentScreen có giá trị
	if (_popupScreen == NULL){
		if (_currentScreen != NULL){
			if (_currentScreen->IsFinished()) // Nếu màn hình hiện tại kết thúc thì hủy nó và chuyển đến màn hình kế tiếp
			{
				CScreen* nextScreen = _currentScreen->GetNextScreen();
				_screenItems.pop_back();
				_screenItems.push_back(nextScreen);
				_currentScreen = _screenItems[0];
				//gameTime->Reset();
			}
			_currentScreen->Update(gameTime);
		}
	}
	else // Nếu có màn hình popup thì cập nhật màn hình này
	{
		_popupScreen->Update(gameTime);
		if (_popupScreen->IsFinished())
			_popupScreen->~CScreen();
	}
}

void CScreenManager::UpdateInput(MKeyboard* input){

	vector<int> list;

	// Nếu không có màn hình popup thì cập nhật màn hình hiện tại đang chạy game
	// Cẩn kiểm tra NULL để xác định biến con trỏ _currentScreen có giá trị
	if (_popupScreen == NULL){
		if (_currentScreen != NULL){
			_currentScreen->UpdateKeyboard(input);
		}
	}
	else // Nếu có màn hình popup thì cập nhật màn hình này
	{
		_popupScreen->UpdateKeyboard(input);
	}
}

CScreen* CScreenManager::GetCurrentScreen(){
	return _currentScreen;
}

void CScreenManager::ShowPopupScreen(CScreen* popupScreen){
	_popupScreen = popupScreen;
	if (_popupScreen != NULL)
	{
		_popupScreen->_camera = _currentScreen->_camera;
		_popupScreen->GetGraphic(_currentScreen->_graphic);
		((CPopup*)_popupScreen)->Initilize();

	}
}