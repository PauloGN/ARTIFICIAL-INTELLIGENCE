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

	void SetSteeringType(bool &seek, bool& flee, bool& arrive, bool& pursuit, bool& evade, Spaceship& agent, const Color& color)
	{
		const float dragSpeed = 0.5f;

		ImGui::DragFloat("MaxSpped: ", &agent.maxSpeed, dragSpeed);


		if (ImGui::Checkbox("Set Seek: ", &seek))
		{
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bPursuit = false;
			agent.bEvade = false;
		}

		if (ImGui::Checkbox("Set Flee: ", &flee))
		{
			agent.bSeek = false;
			agent.bArrive = false;
			agent.bPursuit = false;
			agent.bEvade = false;
		}

		if (ImGui::Checkbox("Set Arrive: ", &arrive))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bPursuit = false;
			agent.bEvade = false;
		}

		if (ImGui::Checkbox("Set Pursuit: ", &pursuit))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bEvade = false;
		}

		if (ImGui::Checkbox("Set Evade: ", &evade))
		{
			agent.bSeek = false;
			agent.bFlee = false;
			agent.bArrive = false;
			agent.bPursuit = false;
		}

		if (agent.bSeek)
		{
			agent.LoadBehavior(ST_Seek, agent.bSeek, true);
			agent.DrawUI(CT_Human, color);
		}

		if (agent.bFlee)
		{
			agent.LoadBehavior(ST_Flee, agent.bFlee, true);
			agent.DrawUI(CT_Human, color);

			ImGui::DragFloat("Panic Radius", &agent.panicRadius, dragSpeed);
			agent.SetPanicRadius(agent.panicRadius);
			DrawCircleLines(agent.posX, agent.posY, agent.panicRadius, color);

		}

		if (agent.bArrive)
		{
			agent.LoadBehavior(ST_Arrive, agent.bArrive, true);
			agent.DrawUI(CT_Human, color);

			ImGui::DragFloat("Decel Tweeker", &agent.tweeker, dragSpeed);
			ImGui::DragFloat("Decel Radius", &agent.radiusDecel, dragSpeed);
			agent.SetDeceleration(agent.tweeker, agent.radiusDecel);
		}

		if (agent.bPursuit)
		{
			agent.LoadBehavior(ST_Pursuit, agent.bPursuit, true);
			agent.DrawUI(CT_AI, color);

			ImGui::DragFloat("Pursuit Y offset", &agent.pursuitOffSet, dragSpeed);
			agent.SetPursuitOffset(agent.pursuitOffSet);
		}

		if (agent.bEvade)
		{
			agent.LoadBehavior(ST_Evade, agent.bEvade, true);
			agent.DrawUI(CT_AI, color);

			ImGui::DragFloat("Evade B offset", &agent.evadeOffSet, dragSpeed);
			agent.SetEvadeOffset(agent.evadeOffSet);
		}

	}

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

	//OtherSpaceship
	otherSpaceship = std::make_unique<Spaceship>(*world.get());
	otherSpaceship->Load("SpaceshipSprites\\spaceshipB_%02i.png", ST_Seek);
	otherSpaceship->posX = 500.0f;
	otherSpaceship->posY = 800.0f;

	//Targets
	spaceship->SetTarget(otherSpaceship.get());
	otherSpaceship->SetTarget(spaceship.get());

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
		SetSteeringType(spaceship.get()->bSeek, spaceship.get()->bFlee, spaceship.get()->bArrive, spaceship.get()->bPursuit, spaceship.get()->bEvade, *spaceship.get(), YELLOW);
	}

	ImGui::End();

	
	//========================================				Blue Spaceship				======================================================\\
	===========================================================================================================================================
	
	ImGui::Begin("Blue SpaceShip", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Blue SpaceShip", &bSelectBlueSpaceShip);

	if (bSelectBlueSpaceShip)
	{
		SetSteeringType(otherSpaceship.get()->bSeek, otherSpaceship.get()->bFlee, otherSpaceship.get()->bArrive, otherSpaceship.get()->bPursuit, otherSpaceship.get()->bEvade, *otherSpaceship.get(), BLUE);
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
