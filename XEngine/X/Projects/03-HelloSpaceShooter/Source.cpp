#include "Bullet.h"
#include "GameManager.h"

GameManager gm;

bool Update(const float dt)
{
	gm.DebugUI();

	//Exit condition
	gm.Update(dt);
	gm.Render();

	const bool bExit = X::IsKeyPressed(X::Keys::ESCAPE);
	return bExit;
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