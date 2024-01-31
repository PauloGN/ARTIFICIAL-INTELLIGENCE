#include "RaveCharacter.h"

RaveCharacter rave;
RaveCharacter rave02;
bool bManualControl = true;

void GameInit()
{
	rave.Initialize("bird.png", 250.0f);
	rave02.Initialize("logo.png", 450.0f);
	rave02.SetbManualControl(false);
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
	rave02.Update(deltaTime);
	rave02.Render();
	//Exit condition
	return X::IsKeyPressed(X::Keys::ESCAPE);
}

void GameCleanup()
{
	rave.CleanUp();
	rave02.CleanUp();
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