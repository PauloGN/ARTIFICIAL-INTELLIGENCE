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

	//Goupe of spaceships
	std::vector<std::unique_ptr<Spaceship>> ships;


	void SetDestination(Spaceship& spaceship)
	{

		if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_RIGHT))
		{
			const float mouseX = GetMousePosition().x;
			const float mouseY = GetMousePosition().y;

			spaceship.DestinationX = mouseX;
			spaceship.DestinationY = mouseY;
		}
	}

	//Debug UI

	bool bSelectYellowSpaceShip = false;
	bool bSelectBlueSpaceShip = false;

	void SetSteeringType(Spaceship& agent, const Color& color)
	{
		const float dragSpeed = 0.5f;

		ImGui::DragFloat("MaxSpped: ", &agent.maxSpeed, dragSpeed);
		ImGui::Checkbox("Debug: ", &agent.bShowDebug);

		if (ImGui::Checkbox("Set Seek: ", &agent.bSeek))
		{
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bPursuit = false;
			agent.bEvade = false;
			agent.bWander = false;
		}

		if (ImGui::Checkbox("Set Flee: ", &agent.bFlee))
		{
			agent.bSeek = false;
			agent.bArrive = false;
			agent.bPursuit = false;
			agent.bEvade = false;
			agent.bWander = false;
		}

		if (ImGui::Checkbox("Set Arrive: ", &agent.bArrive))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bPursuit = false;
			agent.bEvade = false;
			agent.bWander = false;
		}

		if (ImGui::Checkbox("Set Pursuit: ", &agent.bPursuit))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bEvade = false;
			agent.bWander = false;
		}

		if (ImGui::Checkbox("Set Evade: ", &agent.bEvade))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bPursuit = false;
			agent.bWander = false;
		}

		if (ImGui::Checkbox("Set Wander: ", &agent.bWander))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bPursuit = false;
			agent.bEvade = false;
		}

		if (agent.bSeek)
		{
			agent.LoadBehavior(ST_Seek, agent.bSeek, agent.bShowDebug);
			agent.DrawUI(CT_Human, color);
		}

		if (agent.bFlee)
		{
			agent.LoadBehavior(ST_Flee, agent.bFlee, agent.bShowDebug);
			agent.DrawUI(CT_Human, color);

			ImGui::DragFloat("Panic Radius", &agent.panicRadius, dragSpeed);
			agent.SetPanicRadius(agent.panicRadius);

			if (agent.bShowDebug)
			{
				DrawCircleLines(agent.posX, agent.posY, agent.panicRadius, color);
			}


		}

		if (agent.bArrive)
		{
			agent.LoadBehavior(ST_Arrive, agent.bArrive, agent.bShowDebug);
			agent.DrawUI(CT_Human, color);

			ImGui::DragFloat("Decel Tweeker", &agent.tweeker, dragSpeed);
			ImGui::DragFloat("Decel Radius", &agent.radiusDecel, dragSpeed);
			agent.SetDeceleration(agent.tweeker, agent.radiusDecel);
		}

		if (agent.bPursuit)
		{
			agent.LoadBehavior(ST_Pursuit, agent.bPursuit, agent.bShowDebug);
			agent.DrawUI(CT_AI, color);

			ImGui::DragFloat("Pursuit Y offset", &agent.pursuitOffSet, dragSpeed);
			agent.SetPursuitOffset(agent.pursuitOffSet);
		}

		if (agent.bEvade)
		{
			agent.LoadBehavior(ST_Evade, agent.bEvade, agent.bShowDebug);
			agent.DrawUI(CT_AI, color);

			ImGui::DragFloat("Evade B offset", &agent.evadeOffSet, dragSpeed);
			agent.SetEvadeOffset(agent.evadeOffSet);
		}

		if (agent.bWander)
		{
			agent.LoadBehavior(ST_Wander, agent.bWander, agent.bShowDebug);
			agent.DrawUI(CT_AI, color);

			ImGui::DragFloat("Wander Radius: ", &agent.wanderRadius, dragSpeed);
			ImGui::DragFloat("Wander Distance: ", &agent.wanderDistance, dragSpeed);
			ImGui::DragFloat("Wander Jitter: ", &agent.wanderJitter, dragSpeed);
			agent.SetupWander(agent.wanderRadius, agent.wanderDistance, agent.wanderJitter);
		}

		if (agent.bShowDebug)
		{
			Color c = color;

			c.a = 40.0f;
			DrawCircleLines(agent.posX, agent.posY, agent.radius, c);
		}


	}

	const uint32_t numOfSpaceShips = 10;
}


void GameInit()
{
	//World
	world = std::make_unique<AI::AIWorld>();

	//Spaceship
	spaceship = std::make_unique<Spaceship>(*world.get());
	spaceship->Load("SpaceshipSprites\\spaceship_%02i.png", ST_Arrive);
	spaceship->posX = 100.0f;
	spaceship->posY = 100.0f;
	spaceship->bArrive = true;

	//OtherSpaceship
	otherSpaceship = std::make_unique<Spaceship>(*world.get());
	otherSpaceship->Load("SpaceshipSprites\\spaceshipB_%02i.png", ST_Wander);
	otherSpaceship->posX = 500.0f;
	otherSpaceship->posY = 800.0f;
	otherSpaceship->bWander = true;

	//Targets
	spaceship->SetTarget(otherSpaceship.get());
	otherSpaceship->SetTarget(spaceship.get());

	//Initialize a banch of spaceships wander mode
	for (size_t i = 0; i < numOfSpaceShips; i++)
	{
		auto& ship = ships.emplace_back(std::make_unique<Spaceship>(*world.get()));
		ship->Load("SpaceshipSprites\\spaceshipB_%02i.png", ST_Wander);
		ship->posX = AI::AIMath::RandomFloat(32.0f, GetScreenWidth());
		ship->posY = AI::AIMath::RandomFloat(32.0f, GetScreenHeight());;
		ship->bWander = true;
	}

}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();

	if (bSelectYellowSpaceShip)
	{
		//Spaceship
		spaceship->Update(deltaTime);
		spaceship->Render();
		SetDestination(*spaceship.get());//move spaceship type controller
	}

	if (bSelectBlueSpaceShip)
	{
		//Other Spaceship
		otherSpaceship->Update(deltaTime);
		otherSpaceship->Render();
		SetDestination(*otherSpaceship.get());//move spaceship type controller
	}

	//Ships

	for (auto& s :ships)
	{
		s->Update(deltaTime);
		s->Render();
		SetDestination(*s.get());//move spaceship type controller
	}

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{
	//Spaceship
}

void RenderDebugUI()
{

	ImGui::Begin("Yellow SpaceShip", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Checkbox("Yellow SpaceShip", &bSelectYellowSpaceShip);
	if (bSelectYellowSpaceShip)
	{

		SetSteeringType(*spaceship.get(), YELLOW);
	}

	ImGui::End();


	//========================================				Blue Spaceship				======================================================\\
	===========================================================================================================================================

	ImGui::Begin("Blue SpaceShip", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Checkbox("Blue SpaceShip", &bSelectBlueSpaceShip);

	if (bSelectBlueSpaceShip)
	{
		SetSteeringType(*otherSpaceship.get(), BLUE);
	}

	ImGui::End();

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
