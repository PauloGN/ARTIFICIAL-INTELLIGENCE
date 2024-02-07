#pragma once
#include "XEngine.h"

class Fighter
{
public:

	void Load(const char* assetName, const float moveSpeed);
	void Unload();
	void Update(const float& deltaTime);
	void Render();

	void SetPosition(const X::Math::Vector2& pos) { mPosition = pos; }
	const X::Math::Vector2& GetPosition()const { return mPosition; }

private:

	X::TextureId mTextureId;
	X::Math::Vector2 mPosition;

	float mMoveSpeed = 0.0f;

};

