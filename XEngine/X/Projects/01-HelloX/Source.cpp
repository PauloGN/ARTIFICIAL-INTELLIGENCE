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
		rave.SetbManualControl(bManualControl);
	}
}

bool GameLoop(float deltaTime)
{
	CheckInput();

	//class calls
	rave.Update(deltaTime);
	rave.Render();

	//Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	rave.CleanUp();
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