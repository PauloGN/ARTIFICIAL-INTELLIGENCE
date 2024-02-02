#include "GameManager.h"

GameManager gm;

bool Update(const float dt)
{
	gm.Render();
	gm.DebugUI();

	return gm.Update(dt);
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