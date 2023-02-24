#include <REngine.h>
#include <iostream>
#include "TileMap.h"
#include "Character.h"
#include "Enemy.h"
#include "Pickup.h"

namespace
{
	std::unique_ptr<AI::AIWorld> world;
	std::unique_ptr<Enemy> enemy;
	std::vector<std::unique_ptr<Pickup>> pickUpsVector;

}


void GameInit()
{
	//01 Map
	TileMap::StaticInitialize();
	TileMap::Get().Load("Level01.txt", "TileSet.txt");
	
	//Main Character
	Character::StaticInitialize();
	Character::Get().Load("CharHero3.png", 100.f, 64, 64, 0, 5, 7, 6, 4, 44, 8, 8, 2);

	//Assignment FSM
	world = std::make_unique<AI::AIWorld>();
	enemy = std::make_unique<Enemy>(*world.get());
	enemy->Load("CharHero4.1.png", 100.f, 64, 64, 0, 5, 7, 6, 4, 44, 8, 8, 2);

	//pickup
	for (size_t i = 0; i < 50; i++)
	{

		auto& newPickup = pickUpsVector.emplace_back(std::make_unique<Pickup>(*world.get()));

		newPickup->Load();
		newPickup->posX = REng::Math::RandomFloat(100.0f, 1500.0f);
		newPickup->posX = REng::Math::RandomFloat(100.0f, 800);

	}

}


bool GameLoop()
{

	const float deltaTime = GetFrameTime();

	//Map
	TileMap::Get().Update(deltaTime);
	//TileMap::Get().Render();

	//Character
	Character::Get().Update(deltaTime);
	Character::Get().Render();

	//Enemy
	enemy->Update(deltaTime);
	enemy->Render();


	//PickUp
	for (auto iter = pickUpsVector.begin(); iter != pickUpsVector.end();)
	{
		Pickup* pickup = iter->get();

		if (pickup->IsComsumed())
		{
			iter = pickUpsVector.erase(iter);
			world->UnregisterEntity(pickup);
		}
		else
		{
			iter++;
		}
	}

	for (auto& obj : pickUpsVector)
	{
		obj->Update(deltaTime);
		obj->Render();
	}



	//exit condition
	bool bIsStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE) || WindowShouldClose();
	return bIsStopped;
}


void GameCleanUp()
{
	//Map
	TileMap::Get().Unload();
	TileMap::Get().StaticTerminate();

	//Char...
	Character::Get().Unload();
	Character::Get().StaticTerminate();

	//Enemy
	enemy->Unload();
}



int main()
{

	REng::Start("MyPathFinding");
	GameInit();

	REng::Run(GameLoop);

	GameCleanUp();
	REng::Stop();

	return 0;
}