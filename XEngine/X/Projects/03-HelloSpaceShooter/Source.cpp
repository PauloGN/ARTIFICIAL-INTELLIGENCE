#include "XEngine.h"


void GameInit()
{

}


bool GameLoop(float deltaTime)
{


	//Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{

}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start();
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();

	return 0;
}