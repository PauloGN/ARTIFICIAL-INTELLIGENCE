#pragma once
#include <AI.h>
#include <REngine.h>
#include "TypeId.h"

class Pickup : public AI::Entity
{

public:

	Pickup(AI::AIWorld& world);

	virtual void Load();
	virtual void Unload();

	virtual void Update(float deltaTime);
	virtual void Render();

	bool IsComsumed() const { return mComsumed; }
	void Consume() { mComsumed = true; }

protected:

	bool mComsumed = false;
	Texture2D mTexture;

};

