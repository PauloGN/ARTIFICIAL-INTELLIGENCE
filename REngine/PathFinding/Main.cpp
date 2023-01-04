#include <REngine.h>
#include <iostream>
#include "TileMap.h"
#include "Character.h"

Character mainChar;


void GameInit()
{
	//01 Map
	TileMap::StaticInitialize();
	TileMap::Get().Load("Level01.txt", "TileSet01.txt");
	mainChar.Load(100.f);
}


bool GameLoop()
{
	//Map
	TileMap::Get().Update(GetFrameTime());
	TileMap::Get().Render();

	mainChar.Update(GetFrameTime());
	mainChar.Render();


	bool bIsStopped = IsKeyPressed(KeyboardKey::KEY_ESCAPE) || WindowShouldClose();
	return bIsStopped;
}


void GameCleanUp()
{
	//Map
	TileMap::Get().Unload();
	TileMap::Get().StaticTerminate();
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