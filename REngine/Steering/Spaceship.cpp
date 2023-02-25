#include "Spaceship.h"
#include "TypeIds.h"

Spaceship::Spaceship(AI::AIWorld& world):Agent(world, T_Spaceship)
{
	for (size_t i = 0; i < mTextures.size(); i++)
	{
		mTextures[i] = Texture2D();
	}
}

void Spaceship::Load()
{
	maxSpeed = 300.0f;

	for (int i = 0; i < mTextures.size(); i++)
	{
		char spriteName[128];

		//load all sprites 
		sprintf_s(spriteName, "SpaceshipSprites\\spaceship_%02i.png", i+1);
		std::string fullPath;
		REng::ResourcesFullPath(spriteName, fullPath);
		mTextures[i] = LoadTexture(fullPath.c_str());
	}
}

void Spaceship::Unload()
{
	//
}

void Spaceship::Update(float deltaTime)
{

	const float agentToDestinationX = DestinationX - posX;
	const float agentToDestinationY = DestinationY - posY;

	const float distanceToDestination = REng::Math::Magnitude({agentToDestinationX, agentToDestinationY});

	if (distanceToDestination > 0.0f)
	{
		const float directionX = agentToDestinationX / distanceToDestination;
		const float directionY = agentToDestinationY / distanceToDestination;

		velovityX = directionX * maxSpeed;
		velovityY = directionY * maxSpeed;

		posX += velovityX * deltaTime;
		posY += velovityY * deltaTime;

		headingX = directionX;
		headingY = directionY;
	}
}

void Spaceship::Render()
{
	//getting the tangent of the angle
	const float angle = atan2(-headingX, headingY) + REng::Math::kPi;
	const float percent = angle / REng::Math::kTwoPi;

	const int frame = static_cast<int>(percent * mTextures.size()) % mTextures.size();

	const int positionX = posX - (mTextures[frame].width * 0.5f);
	const int positionY = posY - (mTextures[frame].width * 0.5f);

	//Draw current sprite 
	DrawTexture(mTextures[frame], positionX, positionY, WHITE);
	//Draw Destination
	DrawCircle(DestinationX, DestinationY, 5.0f, RED);
}
