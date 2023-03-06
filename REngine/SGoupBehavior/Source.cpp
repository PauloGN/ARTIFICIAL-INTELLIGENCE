#include <REngine.h>
#include <AI.h>
#include "Spaceship.h"

namespace
{
	//World
	std::unique_ptr<AI::AIWorld> world;

	//Spaceship
	std::unique_ptr<Spaceship> spaceship;

	//Goup of spaceships
	using shipsCollection = std::vector<std::unique_ptr<Spaceship>>;
	shipsCollection ships;

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


	void SetSteeringTypeInGroup(shipsCollection& ships, const Color& color)
	{
		ImGui::Text("GROUP SECTION");
		const float dragSpeed = 0.5f;
		static float sMaxSpeed = 100.0f;

		static bool sbShowDebug = true;

		static bool sbSeek = false;
		static bool sbFlee = false;
		static bool sbArrive = false;
		static bool sbPursuit = false;
		static bool sbEvade = false;
		static bool sbWander = true;



		ImGui::DragFloat("G MaxSpped: ", &sMaxSpeed, dragSpeed);
		ImGui::Checkbox("G Debug: ", &sbShowDebug);

		for (auto& ship : ships)
		{
			ship->maxSpeed = sMaxSpeed;
			ship->bShowDebug = sbShowDebug;
		}


		if (ImGui::Checkbox("G Set Seek: ", &sbSeek))
		{
			sbFlee = false;
			sbArrive = false;
			sbPursuit = false;
			sbEvade = false;
			sbWander = false;	
		}

		if (ImGui::Checkbox("G Set Flee: ", &sbFlee))
		{
			sbSeek = false;
			sbArrive = false;
			sbPursuit = false;
			sbEvade = false;
			sbWander = false;
		}

		if (ImGui::Checkbox("G Set Arrive: ", &sbArrive))
		{

			sbSeek = false;
			sbFlee = false;
			sbPursuit = false;
			sbEvade = false;
			sbWander = false;
		}

		if (ImGui::Checkbox("G Set Pursuit: ", &sbPursuit))
		{

			sbPursuit = sbPursuit;
			sbSeek = false;
			sbFlee = false;
			sbArrive = false;
			sbEvade = false;
			sbWander = false;
		}

		if (ImGui::Checkbox("G Set Evade: ", &sbEvade))
		{

			sbSeek = false;
			sbFlee = false;
			sbArrive = false;
			sbPursuit = false;
			sbWander = false;

		}

		if (ImGui::Checkbox("G Set Wander: ", &sbWander))
		{
			sbSeek = false;
			sbFlee = false;
			sbArrive = false;
			sbPursuit = false;
			sbEvade = false;
		}

		for (auto& ship : ships)
		{
			ship->bSeek = sbSeek;
			ship->bFlee = sbFlee;
			ship->bArrive = sbArrive;
			ship->bPursuit = sbPursuit;
			ship->bEvade = sbEvade;
			ship->bWander = sbWander;
		}


		for (auto& agent : ships)
		{
			if (agent->bSeek)
			{
				agent->LoadBehavior(ST_Seek, agent->bSeek, agent->bShowDebug);
				agent->DrawUI(CT_Human, color);
			}

			if (agent->bFlee)
			{
				agent->LoadBehavior(ST_Flee, agent->bFlee, agent->bShowDebug);
				agent->DrawUI(CT_Human, color);

				ImGui::DragFloat("Panic Radius", &agent->panicRadius, dragSpeed);
				agent->SetPanicRadius(agent->panicRadius);

				if (agent->bShowDebug)
				{
					DrawCircleLines(agent->posX, agent->posY, agent->panicRadius, color);
				}


			}

			if (agent->bArrive)
			{
				agent->LoadBehavior(ST_Arrive, agent->bArrive, agent->bShowDebug);
				agent->DrawUI(CT_Human, color);

				ImGui::DragFloat("Decel Tweeker", &agent->tweeker, dragSpeed);
				ImGui::DragFloat("Decel Radius", &agent->radiusDecel, dragSpeed);
				agent->SetDeceleration(agent->tweeker, agent->radiusDecel);
			}

			if (agent->bPursuit)
			{
				agent->LoadBehavior(ST_Pursuit, agent->bPursuit, agent->bShowDebug);
				agent->DrawUI(CT_AI, color);

				ImGui::DragFloat("Pursuit Y offset", &agent->pursuitOffSet, dragSpeed);
				agent->SetPursuitOffset(agent->pursuitOffSet);
			}

			if (agent->bEvade)
			{
				agent->LoadBehavior(ST_Evade, agent->bEvade, agent->bShowDebug);
				agent->DrawUI(CT_AI, color);

				ImGui::DragFloat("Evade B offset", &agent->evadeOffSet, dragSpeed);
				agent->SetEvadeOffset(agent->evadeOffSet);
			}

			if (agent->bWander)
			{
				agent->LoadBehavior(ST_Wander, agent->bWander, agent->bShowDebug);
				agent->DrawUI(CT_AI, color);

				ImGui::DragFloat("Wander Radius: ", &agent->wanderRadius, dragSpeed);
				ImGui::DragFloat("Wander Distance: ", &agent->wanderDistance, dragSpeed);
				ImGui::DragFloat("Wander Jitter: ", &agent->wanderJitter, dragSpeed);
				agent->SetupWander(agent->wanderRadius, agent->wanderDistance, agent->wanderJitter);
			}

			if (agent->bShowDebug)
			{
				Color c = color;

				c.a = 40.0f;
				DrawCircleLines(agent->posX, agent->posY, agent->radius, c);
			}


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


	//Initialize a banch of spaceships wander mode
	for (size_t i = 0; i < numOfSpaceShips; i++)
	{
		auto& ship = ships.emplace_back(std::make_unique<Spaceship>(*world.get()));
		ship->Load("SpaceshipSprites\\spaceshipB_%02i.png", ST_Wander);
		ship->posX = AI::AIMath::RandomFloat(32.0f, GetScreenWidth());
		ship->posY = AI::AIMath::RandomFloat(32.0f, GetScreenHeight());;
		ship->bWander = true;
		ship->SetTarget(spaceship.get());
	}

	//Targets
	spaceship->SetTarget(ships[0].get());
}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();

	//Spaceship
	if (bSelectYellowSpaceShip)
	{
		spaceship->Update(deltaTime);
		spaceship->Render();
		SetDestination(*spaceship.get());//move spaceship type controller
	}

	//Ships
	if (bSelectBlueSpaceShip)
	{
		for (auto& s : ships)
		{
			s->Update(deltaTime);
			s->Render();
			SetDestination(*s.get());//move spaceship type controller
		}
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


	//========================================				Blue Spaceships				======================================================\\
	===========================================================================================================================================

	ImGui::Begin("Blue SpaceShip", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::Checkbox("Blue SpaceShip", &bSelectBlueSpaceShip);

	if (bSelectBlueSpaceShip)
	{
		SetSteeringTypeInGroup(ships, GREEN);
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
