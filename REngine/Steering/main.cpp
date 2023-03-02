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
		spaceship.maxSpeed = 300.0f;

			if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT))
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

	bool bYSeek;
	bool bYFlee;
	bool bYArrive;
	bool bYPursuit;
	bool bYEvade;

	bool bBSeek;
	bool bBFlee;
	bool bBArrive;
	bool bBPursuit;
	bool bBEvade;


	void SetSteeringType(bool &seek, bool& flee, bool& arrive, bool& pursuit, bool& evade)
	{

		if (ImGui::Checkbox("Set Seek: ", &seek))
		{
			bYFlee = false;
			bYArrive = false;
			bYPursuit = false;
			bYEvade = false;
		}

		if (ImGui::Checkbox("Set Flee: ", &flee))
		{
			bYSeek = false;
			bYArrive = false;
			bYPursuit = false;
			bYEvade = false;
		}

		if (ImGui::Checkbox("Set Arrive: ", &arrive))
		{
			bYSeek = false;
			bYFlee = false;
			bYPursuit = false;
			bYEvade = false;
		}

		if (ImGui::Checkbox("Set Pursuit: ", &pursuit))
		{
			bYSeek = false;
			bYFlee = false;
			bYArrive = false;
			bYEvade = false;
		}

		if (ImGui::Checkbox("Set Evade: ", &evade))
		{
			bYSeek = false;
			bYFlee = false;
			bYArrive = false;
			bYPursuit = false;
		}
		
	}

	void SetSteeringTypeB(bool& seek, bool& flee, bool& arrive, bool& pursuit, bool& evade)
	{

		if (ImGui::Checkbox("Set Seek: ", &seek))
		{
			bBFlee = false;
			bBArrive = false;
			bBPursuit = false;
			bBEvade = false;
		}

		if (ImGui::Checkbox("Set Flee: ", &flee))
		{
			bBSeek = false;
			bBArrive = false;
			bBPursuit = false;
			bBEvade = false;
		}

		if (ImGui::Checkbox("Set Arrive: ", &arrive))
		{
			bBSeek = false;
			bBFlee = false;
			bBPursuit = false;
			bBEvade = false;
		}

		if (ImGui::Checkbox("Set Pursuit: ", &pursuit))
		{
			bBSeek = false;
			bBFlee = false;
			bBArrive = false;
			bBEvade = false;
		}

		if (ImGui::Checkbox("Set Evade: ", &evade))
		{
			bBSeek = false;
			bBFlee = false;
			bBArrive = false;
			bBPursuit = false;
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

		SetSteeringType(bYSeek, bYFlee, bYArrive, bYPursuit, bYEvade);

		if (bYSeek )
		{
			spaceship->LoadBehavior(ST_Seek, bYSeek, true);
			spaceship->DrawUI(CT_Human, YELLOW);
		}

		if (bYFlee)
		{
			spaceship->LoadBehavior(ST_Flee, bYFlee, true);
			spaceship->DrawUI(CT_Human, YELLOW);

			ImGui::DragFloat("Panic Radiu", &spaceship->panicRadius);
			spaceship->SetPanicRadius(spaceship->panicRadius);
			DrawCircleLines(spaceship.get()->posX, spaceship.get()->posY, spaceship->panicRadius, YELLOW);

		}

		if (bYArrive)
		{
			spaceship->LoadBehavior(ST_Arrive, bYArrive, true);
			spaceship->DrawUI(CT_Human, YELLOW);
		}

		if (bYPursuit)
		{
			spaceship->LoadBehavior(ST_Pursuit, bYPursuit, true);
			spaceship->DrawUI(CT_AI, YELLOW);
		}

		if (bYEvade)
		{	
			spaceship->LoadBehavior(ST_Evade, bYEvade, true);
			spaceship->DrawUI(CT_AI, YELLOW);
		}
	}

	ImGui::End();

	
	//  **************************							Blue Spaceship							******************************************************   \\
	
	ImGui::Begin("Blue SpaceShip", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::Checkbox("Blue SpaceShip", &bSelectBlueSpaceShip);

	if (bSelectBlueSpaceShip)
	{

		SetSteeringTypeB(bBSeek, bBFlee, bBArrive, bBPursuit, bBEvade);

		if (bBSeek)
		{
			otherSpaceship->LoadBehavior(ST_Seek, bBSeek, true);
			otherSpaceship->DrawUI(CT_Human, BLUE);
		}

		if (bBFlee)
		{
			otherSpaceship->LoadBehavior(ST_Flee, bBFlee, true);
			otherSpaceship->DrawUI(CT_Human, BLUE);

			ImGui::DragFloat("Panic Radiu", &otherSpaceship->panicRadius);
			otherSpaceship->SetPanicRadius(otherSpaceship->panicRadius);
			DrawCircleLines(otherSpaceship.get()->posX, otherSpaceship.get()->posY, otherSpaceship->panicRadius ,BLUE);

		}

		if (bBArrive)
		{
			otherSpaceship->LoadBehavior(ST_Arrive, bBArrive, true);
			otherSpaceship->DrawUI(CT_Human, BLUE);
		}

		if (bBPursuit)
		{
			otherSpaceship->LoadBehavior(ST_Pursuit, bBPursuit, true);
			otherSpaceship->DrawUI(CT_AI, BLUE);
		}

		if (bBEvade)
		{
			otherSpaceship->LoadBehavior(ST_Evade, bBEvade, true);
			otherSpaceship->DrawUI(CT_AI, BLUE);
		}

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
