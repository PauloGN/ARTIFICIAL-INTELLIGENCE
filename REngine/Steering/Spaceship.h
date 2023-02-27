#pragma once

#include "AI.h"
#include "REngine.h"
#include "TypeIds.h"

	enum SteeringType
	{
		ST_Seek,
		ST_Flee,
		ST_Arrive,
		ST_Pursuit,
		ST_Evade
	};

class Spaceship : public AI::Agent
{
public:


public:

	Spaceship(AI::AIWorld& world);

	void Load(const char* SpriteNameformat, SteeringType steeringType);
	void Unload();
	void Update(float deltaTime);
	void Render();
	void DrawUI(ControllerType controllerType);

private:

	//controls all inner behaviors
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	//sprites to draw
	std::array<Texture2D, 16> mTextures;
	//Keep The reference for steering behavior as a week pointer
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::FleeBehavior* mFleeBehavior = nullptr;
	AI::ArriveBehavior* mArriveBehavior = nullptr;
	AI::PursuitBehavior* mPursuitBehavior = nullptr;
	AI::EvadeBehavior* mEvadeBehavior = nullptr;

	
	SteeringType mSteeringType = ST_Seek;
	void SetSteeringType(SteeringType steeringType);

};
