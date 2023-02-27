#include "Spaceship.h"
#include "TypeIds.h"


namespace
{

	//	const float agentToDestinationX = DestinationX - posX;
	//	const float agentToDestinationY = DestinationY - posY;

	//	const float distanceToDestination = REng::Math::Magnitude({ agentToDestinationX, agentToDestinationY });

	//	if (distanceToDestination > 0.0f)
	//	{
	//		const float directionX = agentToDestinationX / distanceToDestination;
	//		const float directionY = agentToDestinationY / distanceToDestination;

	//		velovityX = directionX * maxSpeed;
	//		velovityY = directionY * maxSpeed;

	//		posX += velovityX * deltaTime;
	//		posY += velovityY * deltaTime;

	//		headingX = directionX;
	//		headingY = directionY;
	//	}

}


Spaceship::Spaceship(AI::AIWorld& world):Agent(world, T_Spaceship)
{
	for (size_t i = 0; i < mTextures.size(); i++)
	{
		mTextures[i] = Texture2D();
	}
}

void Spaceship::Load()
{
	//Inherited properties from Agent
	maxSpeed = 300.0f;

	//Load the steering behaviors
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	//mSeekBehavior = mSteeringModule->AddBehavior<AI::SeekBehavior>();//the week pointer caches whatever it returns
	//mFleeBehavior = mSteeringModule->AddBehavior<AI::FleeBehavior>();//the week pointer caches whatever it returns
	//mFleeBehavior->SetActive(true);
	//mFleeBehavior->ShowDebug(true);

	mArriveBehavior = mSteeringModule->AddBehavior<AI::ArriveBehavior>();//the week pointer caches whatever it returns
	mArriveBehavior->SetActive(true);
	mArriveBehavior->ShowDebug(true);

	//load all sprites 
	for (int i = 0; i < mTextures.size(); i++)
	{
		char spriteName[128];

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

	const std::pair<float, float> force = mSteeringModule->Calculate();
	const float accelerationX = force.first / mass;
	const float accelerationY = force.second / mass;

	velovityX += accelerationX * deltaTime;
	velovityY += accelerationY * deltaTime;

	posX += velovityX * deltaTime;
	posY += velovityY * deltaTime;

	//Truncate speed to not exceed max speed
	if (REng::Math::MagnitudeSqr({velovityX, velovityY}) > REng::Math::Sqr(maxSpeed))
	{
		REng::Math::Vector2 velocity = REng::Math::Normalize({velovityX, velovityY}) * maxSpeed;

		velovityX = velocity.x;
		velovityY = velocity.y;
	}

	//Screen Wrapping
	const auto screenWidth = GetScreenWidth();
	const auto screenHeight = GetScreenHeight();

	//Right and left
	if (posX < 0.0f)
	{
		posX += screenWidth;
	}

	if (posX >= screenWidth)
	{
		posX -= screenWidth;
	}

	//UP and Down
	if (posY < 0.0f)
	{
		posY += screenHeight;
	}
	if (posY >= screenHeight)
	{
		posY -= screenHeight;
	}

	//update heading if you have movement
	if (REng::Math::MagnitudeSqr({velovityX, velovityY}) > 1.0f )
	{
		REng::Math::Vector2 velocity = REng::Math::Normalize({ velovityX, velovityY });

		headingX = velocity.x;
		headingY = velocity.y;
	}

}

void Spaceship::Render()
{
	//getting the tangent of the angle
	const float angle = atan2(-headingX, headingY) + REng::Math::kPi;
	const float percent = angle / REng::Math::kTwoPi;

	const int frame = static_cast<int>(percent * mTextures.size()) % mTextures.size();

	const int positionX = posX - (mTextures[frame].width * 0.5f);
	const int positionY = posY - (mTextures[frame].height * 0.5f);

	//Draw current sprite 
	DrawTexture(mTextures[frame], positionX, positionY, WHITE);
	//Draw Destination
	DrawCircle(DestinationX, DestinationY, 5.0f, RED);
}
