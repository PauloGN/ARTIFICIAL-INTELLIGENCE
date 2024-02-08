#pragma once
#include "XEngine.h"

class Bullet
{
public:

	void Load(const char* assetName, const float moveSpeed);
	void Unload();
	void Update(const float& deltaTime);
	void Render();

	void Fire(const X::Math::Vector2& pos, const X::Math::Vector2& dir);
	void Deactivate();

	bool IsActive() const { return mActive; }

private:

	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mDirection;
	float mMoveSpeed = 0.0f;

	void Move(const float& deltaTime);

	//ObjectPooling
	bool mActive = false;

	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;
};
