#include "Pickup.h"

namespace
{

	Types T_type;

}

Pickup::Pickup(AI::AIWorld& world):Entity(world , Types::T_Apple)
{
	T_type = Types::T_Apple;
	mTexture = Texture2D();
}

void Pickup::Load()
{

	std::string spritePath;

	switch (T_type)
	{
	case T_Apple:

		REng::ResourcesFullPath("Apple.png", spritePath);

		break;
	case T_Orange:
		REng::ResourcesFullPath("Apple.png", spritePath);

		break;
	case T_Weapon:
		REng::ResourcesFullPath("Apple.png", spritePath);

		break;
	default:
		REng::ResourcesFullPath("Fire.png.png", spritePath);
		break;
	}

	mTexture = LoadTexture(spritePath.c_str());
}

void Pickup::Unload()
{}

void Pickup::Update(float deltaTime)
{}

void Pickup::Render()
{

	const float X = posX - mTexture.width * 0.5f;
	const float Y = posX - mTexture.width * 0.5f;

	DrawTexture(mTexture, X,Y, WHITE);

}
