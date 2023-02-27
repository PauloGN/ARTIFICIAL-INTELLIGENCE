#include <REngine.h>
#include <AI.h>
#include "Spaceship.h"

namespace
{
	//World
	std::unique_ptr<AI::AIWorld> world;
	
	//Spaceship
	std::unique_ptr<Spaceship> spaceship;
	void SetDestination(Spaceship& spaceship, ControllerType controller)
	{

		switch (controller)
		{
		case CT_Human:

			if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
			{
				const float mouseX = GetMousePosition().x;
				const float mouseY = GetMousePosition().y;

				spaceship.DestinationX = mouseX;
				spaceship.DestinationY = mouseY;
			}
			break;

		case CT_AI:


			break;
		default:
			break;
		}

	}

}


void GameInit()
{
	//World
	world = std::make_unique<AI::AIWorld>();

	//Spaceship
	spaceship = std::make_unique<Spaceship>(*world.get());
	spaceship->Load("SpaceshipSprites\\spaceshipB_%02i.png", ST_Seek);
	spaceship->posX = 100.0f;
	spaceship->posY = 100.0f;

	//OtherSpaceship
}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();
	
	//Spaceship
	spaceship->Update(deltaTime);
	spaceship->Render();
	spaceship->DrawUI(CT_Human);
	SetDestination(*spaceship.get(), CT_Human);//move spaceship type controller

	//Other Spaceship

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{
	//Spaceship
}

void RenderDebugUI()
{
}

int main()
{
	REng::Start("Steering");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}
