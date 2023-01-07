#include "Character.h"

namespace
{

	const float spritXoffset = 54.7;
	const float spritYoffset = 58.9;

	std::unique_ptr<Character> charInstance;

}

void Character::StaticInitialize()
{
	assert(charInstance == nullptr, "charInstance already instantiated...\n");
	charInstance = std::make_unique<Character>();
}

void Character::StaticTerminate()
{
	charInstance.reset();
}

Character& Character::Get()
{
	assert(charInstance != nullptr, "charInstance not created yet must call StaticInitialize() first.\n");
	return *charInstance;
}

void Character::Load(const float initialSpeed)
{

	initialSpeed > 1.f ? mMoveSpeed = initialSpeed : mMoveSpeed = 45.f;

	std::string fullPath;
	REng::ResourcesFullPath("CharHero.png", fullPath);

	//Rectangle initial position and size
	const int yInitialSpriteRowNumber = 8;//go down 8 rows
	mRecSprite.x = 0.f;
	mRecSprite.y = yInitialSpriteRowNumber * spritYoffset; 
	mRecSprite.width = spritXoffset;
	mRecSprite.height = spritYoffset;

	//load sprite sheet
	mCharTexture = LoadTexture(fullPath.c_str());
	bIsMoving = false;
}

void Character::Unload()
{

	mMoveSpeed = 0.f;
	mCharTexture = Texture2D();
	mPlayerPos = REng::Math::Vector2(100.f, 100.f);
	mRecSprite = Rectangle();
	bIsMoving = false;
	currentTime = 0.f;
	currentSprite = 0;

}

void Character::Update(float deltaTime)
{
	PlayerMovement(deltaTime);
}

void Character::Render()
{
	
	//DrawTexture(mCharTexture, mPlayerPos.x, mPlayerPos.y, WHITE);
	DrawTextureRec(mCharTexture, mRecSprite, {mPlayerPos.x, mPlayerPos.y}, WHITE);
}

Character::Character()
{
	mMoveSpeed = 0.f;
	mCharTexture = Texture2D();
	mPlayerPos = REng::Math::Vector2(100.f, 100.f);
	mRecSprite = Rectangle();
	bIsMoving = false;
	currentTime = 0.f;
	currentSprite = 0;
}


void Character::PlayerMovement(float deltaTime)
{

	if (IsKeyDown(KeyboardKey::KEY_RIGHT))
	{
	
		float xRecPos = 0.f;
		const int yRecPos = spritYoffset * 7;
		const int maxNumbersOfSprites = 10;

		const float animationMaxTime = .2f;

		currentTime += deltaTime;
		if (currentTime >= animationMaxTime)
		{
			xRecPos = spritXoffset * currentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			currentTime = 0.f;
			if (currentSprite >= maxNumbersOfSprites)
			{
				currentSprite = 0;
			}
		}

		mPlayerPos.x += mMoveSpeed * deltaTime;
	}

	


	if (IsKeyDown(KeyboardKey::KEY_LEFT))
	{
		float xRecPos = 0.f;
		const int yRecPos = spritYoffset * 5;
		const int maxNumbersOfSprites = 10;

		float animationMaxTime = .2f;

		currentTime += deltaTime;
		if (currentTime >= animationMaxTime)
		{
			xRecPos = spritXoffset * currentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			currentTime = 0.f;
			if (currentSprite >= maxNumbersOfSprites)
			{
				currentSprite = 0;
			}
		}

		mPlayerPos.x -= mMoveSpeed * deltaTime;
	}

	if (IsKeyDown(KeyboardKey::KEY_UP))
	{
		float xRecPos = 0.f;
		const int yRecPos = spritYoffset * 6;
		const int maxNumbersOfSprites = 10;

		float animationMaxTime = .2f;

		currentTime += deltaTime;
		if (currentTime >= animationMaxTime)
		{
			xRecPos = spritXoffset * currentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			currentTime = 0.f;
			if (currentSprite >= maxNumbersOfSprites)
			{
				currentSprite = 0;
			}
		}

		mPlayerPos.y -= mMoveSpeed * deltaTime;
	}


	if (IsKeyDown(KeyboardKey::KEY_DOWN))
	{
		float xRecPos = 0.f;
		const int yRecPos = spritYoffset * 4;
		const int maxNumbersOfSprites = 10;

		float animationMaxTime = .2f;

		currentTime += deltaTime;
		if (currentTime >= animationMaxTime)
		{
			xRecPos = spritXoffset * currentSprite++;
			UpdateRecSprite(true, xRecPos, yRecPos);
			currentTime = 0.f;
			if (currentSprite >= maxNumbersOfSprites)
			{
				currentSprite = 0;
			}
		}


		mPlayerPos.y += mMoveSpeed * deltaTime;
	}


	if (!bIsMoving)
	{
		Idle(deltaTime);
	}

	bIsMoving = false;

}

void Character::Idle(float deltaTime)
{

	float xRecPos = 0.f;
	const int yRecPos = 0;
	const int maxNumbersOfSprites = 3;

	float animationMaxTime = .5f;

	currentTime += deltaTime;
	if (currentTime >= animationMaxTime)
	{
		
		xRecPos = spritXoffset * (currentSprite % maxNumbersOfSprites);
		currentSprite++;
		UpdateRecSprite(false, xRecPos, yRecPos);
		currentTime = 0.f;
		if (currentSprite >= maxNumbersOfSprites)
		{
			currentSprite = 0;
		}
	}

}

void Character::UpdateRecSprite(bool isMoving, const float recX, const float recY)
{
	bIsMoving = isMoving;
	mRecSprite.x = recX;
	mRecSprite.y = recY;
}
