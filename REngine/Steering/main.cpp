#include <REngine.h>
#include <AI.h>
#include "Spaceship.h"

namespace
{
	//World
	std::unique_ptr<AI::AIWorld> world;
	
	//Spaceship
	std::unique_ptr<Spaceship> spaceship;


	void SetDestination(Spaceship& spaceship)
	{

		if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
		{
			const float mouseX = GetMousePosition().x;
			const float mouseY = GetMousePosition().y;

			spaceship.DestinationX = mouseX;
			spaceship.DestinationY = mouseY;
		}
	}

}


void GameInit()
{
	//World
	world = std::make_unique<AI::AIWorld>();

	//Spaceship
	spaceship = std::make_unique<Spaceship>(*world.get());
	spaceship->Load();
	spaceship->posX = 100.0f;
	spaceship->posY = 90.0f;
}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();
	
	//Spaceship
	spaceship->Update(deltaTime);
	spaceship->Render();
	SetDestination(*spaceship.get());

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
