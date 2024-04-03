#pragma once
#include "XEngine.h"

class Fighter
{
public:

	//Base functions
	void Load(const char* assetName, const float moveSpeed);
	void Unload();
	void Update(const float& deltaTime);
	void Render();

	//Getters And Setters
	void SetPosition(const X::Math::Vector2& pos) { mPosition = pos; }

	const X::Math::Vector2& GetPosition() const { return mPosition; }

private:

	X::TextureId mTextureId = 0;
	X::Math::Vector2 mPosition;
	X::Math::Vector2 mDirection;

	float mMoveSpeed = 0.0f;

	void Move(const float& deltaTime);
};