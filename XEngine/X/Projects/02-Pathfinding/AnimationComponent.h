#pragma once
#include <map>
#include <string>

class Animation;
class CharacterBase;

class AnimationComponent final
{
public:

	AnimationComponent(CharacterBase* _charBase_ptr);
	~AnimationComponent() = default;

	void UpdateAnimation(const float& _dt);
	void ChangeAnimation(const char* animName);
	bool DoesAnimationExist(const char* animName);
	void AddAnimation(const char* key, Animation* anim);

	void CleanUp();

	void LoadAnimation(const char* filePath);

protected:

	std::map<std::string, Animation*> animations;
	Animation* currentAnimation;
	CharacterBase* charBase_ptr;
	float currentTime;
	int currentSprite;
};