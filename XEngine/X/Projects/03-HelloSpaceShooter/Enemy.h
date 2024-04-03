#pragma once

#include <XEngine.h>

class Enemy
{
public:

	//Standard object functions
	void Load();
	void Unload();
	void Update(const float& deltaTime);
	void Render();

	//Class specialized function
	void Spawn(const X::Math::Vector2& position);
	void Kill();
	X::Math::Circle GetBoundingCircle() const;

	//Getters and Setters
	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }

private:

	X::TextureId mTexture = 0;
	X::Math::Vector2 mVelocity;
	X::Math::Vector2 mPosition;

	//Object pooling
	bool mActive = false;
	float mDelay = 0.0f;
	float mHalfSpriteWidth = 0.0f;
};

