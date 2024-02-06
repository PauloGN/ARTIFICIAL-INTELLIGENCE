#include "GameManager.h"

GameManager gm;

bool Update(const float dt)
{
	gm.DebugUI();
	
	const bool close = gm.Update(dt);
	gm.Render();
	return close;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	gm.Initialize();

	X::Run(Update);

	gm.CleanUp();
	X::Stop();

	return 0;
}