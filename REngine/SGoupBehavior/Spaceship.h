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
		ST_Evade,
		ST_Wander
	};

class Spaceship : public AI::Agent
{
public:


public:

	Spaceship(AI::AIWorld& world);

	void Load(const char* SpriteNameformat, SteeringType steeringType);
	void LoadBehavior(SteeringType st_type, bool activate, bool debug);
	void Unload();
	void Update(float deltaTime);
	void Render();
	void DrawUI(ControllerType controllerType, const Color& color);

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
	AI::WanderBehavior* mWanderBehavior = nullptr;

	//Group Behavior
	AI::SeparationBehavior* mSeparationBehavior;
	AI::AlignmentBehavior* mAlignmentBehavior;

	
	SteeringType mSteeringType = ST_Seek;
	void SetSteeringType(SteeringType steeringType);

public:

	//inner behaviors control

	///////   FLEE    \\\\\\
	
	void SetPanicRadius(const float panicRadius);
	float panicRadius;

	/////  Pursuit \\\\\

	float pursuitOffSet;
	void SetPursuitOffset(const float offset);

	/////  Evade \\\\\

	float evadeOffSet;
	void SetEvadeOffset(const float offset);

	///// Arrive  \\\\

	float tweeker;
	float radiusDecel;
	void SetDeceleration(const float tw,const float rd);


	///// Wander \\\\\

	float wanderDistance = 10.0f;
	float wanderRadius = 5.0f;
	float wanderJitter = 1.0f;

	void SetupWander(const float radius, const float distance, const float jitter);

	//// FLOCKING   \\\\


	void SetSeparation(bool separation);
	void SetSeparationForcePercentage(const float percent);


	void SetAlignment(bool alignm);
	void SetAlignmentForcePercentage(const float percent);

	// Steering types as booleans

	bool bShowDebug = true;

	bool bSeek;
	bool bFlee;
	bool bArrive;
	bool bPursuit;
	bool bEvade;
	bool bWander;

};
