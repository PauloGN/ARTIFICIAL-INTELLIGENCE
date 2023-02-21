#include <REngine.h>
#include <AI.h>
#include "Ninja.h"
#include "Monster.h"
#include "Bank.h"
#include "Shelter.h"


namespace
{
	std::unique_ptr<AI::AIWorld> world;
	std::unique_ptr<Ninja> ninja;
	std::unique_ptr<Bank> bank;
	std::unique_ptr<Bank> bank_2;
	std::unique_ptr<Shelter> shelter;
	std::vector<std::unique_ptr<Monster>> monsters;

	const int maxNumberOfEnemies = 10;
	int currentNumberOfEnemies = 10;
}


void GameInit()
{
	world = std::make_unique<AI::AIWorld>();
	ninja = std::make_unique<Ninja>(*world.get());
	ninja->Load("CharHero4.1.png", 100.f, 64, 64, 0, 5, 7, 6, 4, 44, 8, 8, 2);

	//Bank
	bank = std::make_unique<Bank>(*world.get());
	bank->Load(1480, 780);
	bank_2 = std::make_unique<Bank>(*world.get());
	bank_2->Load(35, 780);
	//Shelter
	shelter = std::make_unique<Shelter>(*world.get());
	shelter->Load(780, 64);

	for (int i = 0; i < maxNumberOfEnemies; ++i)
	{
		monsters.emplace_back(std::make_unique<Monster>(*world.get()));
		monsters[i]->Load(i);
		monsters[i]->posX = {REng::Math::RandomFloat(100.0f, 1530.0f)};
		monsters[i]->posY = {REng::Math::RandomFloat(100.0f, 500.0f) };
	}
}

bool GameUpdate()
{
	float deltaTime = GetFrameTime();
	ninja->Update(deltaTime);
	ninja->Render();


	// ----------------------------------------          Monster

	for (auto iter = monsters.begin(); iter != monsters.end();)
	{
		Monster* monster = iter->get();
		if (monster->IsDesfeated())
		{
			iter = monsters.erase(iter);
			world->UnregisterEntity(monster);
			break;
		}
		else
		{
			iter++;
		}
	}

	//Update Mosters
	for (auto& monster : monsters)
	{
		monster->Update(deltaTime);
		monster->Render();
	}

	//Reset Monsters
	if (monsters.size() <= 0)
	{
		for (int i = 0; i < maxNumberOfEnemies; ++i)
		{
			monsters.emplace_back(std::make_unique<Monster>(*world.get()));
			monsters[i]->Load(i);
			monsters[i]->posX = { REng::Math::RandomFloat(100.0f, 1600.0f) };
			monsters[i]->posY = { REng::Math::RandomFloat(100.0f, 500.0f) };
		}
	}


	// ================ Bank

	bank->Update(deltaTime);
	bank->Render();

	bank_2->Update(deltaTime);
	bank_2->Render();

	// ================ Shelter

	shelter->Update(deltaTime);
	shelter->Render();

	bool isStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE);
	return isStopped;
}

void GameCleanup()
{

}

void RenderDebugUI()
{}

int main()
{
	REng::Start("FSM");
	GameInit();
	REng::Run(GameUpdate, RenderDebugUI);
	GameCleanup();
	REng::Stop();
	return 0;
}
