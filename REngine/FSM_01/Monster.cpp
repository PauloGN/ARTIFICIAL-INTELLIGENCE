#include "Monster.h"
#include "TypeId.h"

Monster::Monster(AI::AIWorld& world):Entity(world, Types::T_Monster)
{
	mTexture = Texture2D();
	bIsDefeated = false;
	mTextureRect = Rectangle();

}

void Monster::Load(int index)
{

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

	//number of animations
	if ((index % monsterNames.size()) == 0)
	{
		mAnimFrames = 8;
	}

}

void Monster::Unload()
{
}

void Monster::Update(float deltaTime)
{
	UpdateAnimation(deltaTime);
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
