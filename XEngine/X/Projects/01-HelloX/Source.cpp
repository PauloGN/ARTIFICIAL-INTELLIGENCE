#include "RaveCharacter.h"

RaveCharacter rave;
bool bManualControl = true;

void GameInit()
{
	rave.Initialize();
}

void CheckInput()
{
	if (X::IsKeyPressed(X::Keys::SPACE))
	{
		bManualControl = !bManualControl;
	}
}

bool GameLoop(float deltaTime)
{
	rave.Render();

	CheckInput();
	// Movement
	if (bManualControl)
	{
		rave.Movement(deltaTime);
	}
	else
	{
		rave.CharAutoMove(deltaTime);
	}

	rave.Update(deltaTime);
	rave.ScreenBoundsControl(bManualControl);

	//Exit condition
	const bool bExit = X::IsKeyPressed(X::Keys::ESCAPE);
	return bExit;
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