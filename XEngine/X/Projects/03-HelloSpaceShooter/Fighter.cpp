#include "Fighter.h"

void Fighter::Load(const char* assetName, const float moveSpeed)
{
	mTextureId = X::LoadTexture(assetName);
	mMoveSpeed = moveSpeed;
}

void Fighter::Unload()
{
	mTextureId = 0;
	mMoveSpeed = 0.0f;
}

void Fighter::Update(const float& deltaTime)
{
}

void Fighter::Render()
{

}
