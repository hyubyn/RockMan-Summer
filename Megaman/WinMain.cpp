#include <Windows.h>
#include "Game.h"
#include "Timer.h"

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPTSTR a, int c)
{
	//Khai báo đối tượng game
	Game game(h,SCREEN_WIDTH,SCREEN_HEIGHT,"Megaman");
	if(!game.InitWindow())
	{
		MessageBox(NULL,"Can't init game","Error",MB_OK);
		return 0;
	}
	//Load data
	game.InitGame();
	//

	CTimer* m_pTimer;
	m_pTimer = CTimer::GetInstance();
	m_pTimer->SetMaxFps((float)GAME_FPS);

	MSG msg;
	int done = 0;
	m_pTimer->StartCount();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (m_pTimer->GetTime() < 1000.0f)
			{
				m_pTimer->EndCount();

				game.Update(m_pTimer);
				game.Render(m_pTimer);
			}
		}
	}
	return 0;
}