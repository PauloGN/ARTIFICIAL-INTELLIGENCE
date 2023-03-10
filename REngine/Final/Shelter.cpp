#include "Shelter.h"
#include "TypeId.h"

Shelter::Shelter(AI::AIWorld& world):Entity(world, Types::T_Shelter)
{
	mTextureFire = Texture2D();
	mTextureShelter = Texture2D();
	mTextureRect = Rectangle();
}

void Shelter::Load(const float X, const float Y)
{
	posX = X;
	posY = Y;
	//load sprite sheet
	std::string fullPath;
	REng::ResourcesFullPath("CampingFire.png", fullPath);
	mTextureFire = LoadTexture(fullPath.c_str());
	fullPath.clear();
	REng::ResourcesFullPath("Shelter.png", fullPath);
	mTextureShelter = LoadTexture(fullPath.c_str());


	//Load Rectangle
	mTextureRect.x = 0.0f;
	mTextureRect.y = 0.0f;
	mTextureRect.width = static_cast<float>(mTextureFire.width) / static_cast<float>(mAnimFrames);
	mTextureRect.height = static_cast<float>(mTextureFire.height);
	bLightFire = false;

}

void Shelter::Unload()
{
}

void Shelter::Update(float deltaTime)
{
	UpdateAnimation(deltaTime);
}

void Shelter::Render()
{
	float halfWidth = mTextureRect.width * 0.5f;
	float halfHeight = mTextureRect.height * 0.5f;

	if (bLightFire)
	{
		DrawTextureRec(mTextureFire, mTextureRect, { posX - halfWidth + 64, posY - halfHeight + 40 }, WHITE);
	}
	DrawTexture(mTextureShelter, posX - halfWidth, posY - halfHeight, WHITE);
}

void Shelter::UpdateAnimation(float deltaTime)
{
	mCurrentTime += deltaTime;
	if (mCurrentTime > mFrameDuration)
	{
		mCurrentFrame += 1;
		mCurrentFrame %= mAnimFrames;
		mCurrentTime = 0.0f;
	}

	mTextureRect.x = static_cast<float>(mCurrentFrame) * static_cast<float>(mTextureFire.width) / static_cast<float>(mAnimFrames);
}
