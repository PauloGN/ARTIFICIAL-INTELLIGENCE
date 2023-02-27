#pragma once

#include "AI.h"
#include "REngine.h"


class Spaceship : public AI::Agent
{
public:
	Spaceship(AI::AIWorld& world);

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();

private:

	//controls all inner behaviors
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	//sprites to draw
	std::array<Texture2D, 16> mTextures;
	//Keep The reference for steering behavior as a week pointer
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
};
