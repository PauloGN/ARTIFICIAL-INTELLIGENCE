#include "Monster.h"
#include "TypeId.h"

Monster::Monster(AI::AIWorld& world):Agent(world, Types::T_Monster)
{
	mTexture = Texture2D();
	bIsDefeated = false;
	mTextureRect = Rectangle();

}

void Monster::Load(int index)
{
	//
	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);
	mWanderBehavior = mSteeringModule->AddBehavior<AI::WanderBehavior>();
	mEvadeBehavior = mSteeringModule->AddBehavior<AI::EvadeBehavior>();
	mWanderBehavior->SetActive(true);
	mWanderBehavior->ShowDebug(false);
	mEvadeBehavior->SetActive(false);
	mEvadeBehavior->ShowDebug(false);
	mEvadeBehavior->SetPredictionPoint(25.0f);


	std::vector<std::string> monsterNames;
	monsterNames.push_back("Flight.png");
	monsterNames.push_back("Goblin.png");
	monsterNames.push_back("Mushroom.png");
	monsterNames.push_back("Skelecton.png");

	//load sprite sheet
	std::string fullPath;
	REng::ResourcesFullPath(monsterNames[index%monsterNames.size()], fullPath);
	mTexture = LoadTexture(fullPath.c_str());

	//Load Rectangle
	mTextureRect.x = 0.0f;
	mTextureRect.y = 0.0f;
	mTextureRect.width = static_cast<float>(mTexture.width) / static_cast<float>(mAnimFrames);
	mTextureRect.height = static_cast<float>(mTexture.height);

	maxSpeed = 50;

}

void Monster::Unload()
{
}

void Monster::Update(float deltaTime)
{
	UpdateAnimation(deltaTime);

	const std::pair<float, float> force = mSteeringModule->Calculate();
	const float accelerationX = force.first / mass;
	const float accelerationY = force.second / mass;

	velovityX += accelerationX * deltaTime;
	velovityY += accelerationY * deltaTime;

	posX += velovityX * deltaTime;
	posY += velovityY * deltaTime;

	//Truncate speed to not exceed max speed
	if (REng::Math::MagnitudeSqr({ velovityX, velovityY }) > REng::Math::Sqr(maxSpeed))
	{
		REng::Math::Vector2 velocity = REng::Math::Normalize({ velovityX, velovityY }) * maxSpeed;

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
	if (REng::Math::MagnitudeSqr({ velovityX, velovityY }) > 1.0f)
	{
		REng::Math::Vector2 velocity = REng::Math::Normalize({ velovityX, velovityY });

		headingX = velocity.x;
		headingY = velocity.y;
	}
}

void Monster::Render()
{
	float halfWidth = mTextureRect.width * 0.5f;
	float halfHeight = mTextureRect.height * 0.5f;

	DrawTextureRec(mTexture, mTextureRect, { posX - halfWidth, posY - halfHeight }, WHITE);
}

void Monster::UpdateAnimation(float deltaTime)
{
	mCurrentTime += deltaTime;
	if (mCurrentTime > mFrameDuration)
	{
		mCurrentFrame += 1;
		mCurrentFrame %= mAnimFrames;
		mCurrentTime = 0.0f;
	}

	mTextureRect.x = static_cast<float>(mCurrentFrame) * static_cast<float>(mTexture.width) / static_cast<float>(mAnimFrames);
}

void Monster::SetWander(bool isActive)
{
	mWanderBehavior->SetActive(isActive);
}

void Monster::SetMaxSpeed(const float maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void Monster::SetEvade(bool isActive)
{

	mEvadeBehavior->SetActive(isActive);
}
