#include "Bank.h"
#include "TypeId.h"

Bank::Bank(AI::AIWorld& world):Entity(world, Types::T_Bank)
{
	mTexture = Texture2D();
}

void Bank::Load()
{
	posX = 1480;
	posY = 780;

	//load sprite sheet
	std::string fullPath;
	REng::ResourcesFullPath("Bank.png", fullPath);
	mTexture = LoadTexture(fullPath.c_str());

}

void Bank::Unload()
{
}

void Bank::Update(float deltaTime)
{
}

void Bank::Render()
{
	DrawTexture(mTexture, posX, posY, WHITE);
}
