#include <REngine.h>
#include <AI.h>
#include "Spaceship.h"

namespace
{
	//World
	std::unique_ptr<AI::AIWorld> world;
	
	//Spaceship
	std::unique_ptr<Spaceship> spaceship;

	//Other Spaceship
	std::unique_ptr<Spaceship> otherSpaceship;


	void SetDestination(Spaceship& spaceship, ControllerType controller)
	{
		spaceship.maxSpeed = 300.0f;
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
	spaceship->Load("SpaceshipSprites\\spaceship_%02i.png", ST_Seek);
	spaceship->posX = 100.0f;
	spaceship->posY = 100.0f;

	//OtherSpaceship
	otherSpaceship = std::make_unique<Spaceship>(*world.get());
	otherSpaceship->Load("SpaceshipSprites\\spaceshipB_%02i.png", ST_Pursuit);
	otherSpaceship->posX = 500.0f;
	otherSpaceship->posY = 800.0f;
	otherSpaceship->SetTarget(spaceship.get());

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
	otherSpaceship->Update(deltaTime);
	otherSpaceship->Render();
	otherSpaceship->DrawUI(CT_AI);
	SetDestination(*spaceship.get(), CT_AI);//move spaceship type controller

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
