#pragma once
#include "XEngine.h"
#include "ImGui/Inc/imgui.h"

class AnimationComponent;
class Animation;

class CharacterBase
{
public:

	CharacterBase();
	virtual ~CharacterBase();
	void Render();

	X::Math::Rect baseRect;
	X::TextureId spriteSheet = 0;
	X::Math::Vector2 spriteOffset;

	//Movement
	X::Math::Vector2 pos;
	X::Math::Vector2 dir;
	float speed = 0;

	AnimationComponent* animationManager;

protected:

	void AddAnimation(const char* animKey, Animation* anim);
};
