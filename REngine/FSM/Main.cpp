#include <REngine.h>
#include <iostream>
#include "TileMap.h"
#include "Character.h"
#include "Enemy.h"

void GameInit()
{
	//01 Map
	TileMap::StaticInitialize();
	TileMap::Get().Load("Level01.txt", "TileSet.txt");
	
	//Main Character
	Character::StaticInitialize();
	Character::Get().Load("CharHero4.1.png", 100.f, 64, 64, 0, 5, 7, 6, 4, 44, 8, 8, 2);

	//Character::Get().Load("CharHero.png", 100.f, 64, 64, 0, 5, 7, 6, 4, 8, 8, 8, 8);

}


bool GameLoop()
{

	const float deltaTime = GetFrameTime();

	//Map
	TileMap::Get().Update(deltaTime);
	TileMap::Get().Render();

	//Character
	Character::Get().Update(deltaTime);
	Character::Get().Render();

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