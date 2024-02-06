#include "AnimationComponent.h"
#include "CharacterBase.h"
#include "Animation.h"

AnimationComponent::AnimationComponent(CharacterBase* _charBase_ptr) :
	currentAnimation (nullptr),
	charBase_ptr(_charBase_ptr)
{
	currentTime = 0;
	currentSprite = 0;
	//~ Set initial frame position for x and y
	charBase_ptr->baseRect.top = 0;
	charBase_ptr->baseRect.bottom = charBase_ptr->spriteOffset.y;
	charBase_ptr->baseRect.left = 0;
	charBase_ptr->baseRect.right = charBase_ptr->spriteOffset.x;

}

void AnimationComponent::UpdateAnimation(const float& _dt)
{
	_ASSERT(charBase_ptr != nullptr && currentAnimation != nullptr, "CharBase_ptr can not be null");

	////
	
	float xRecPos = 0.f;
	const float yRecPos = currentAnimation->yFrameRow * charBase_ptr->spriteOffset.y;
	const int maxNumbersOfSprites = currentAnimation->numOfFrames;

	currentTime += _dt;
	if (currentTime >= currentAnimation->animFrameRate)
	{
		xRecPos = charBase_ptr->spriteOffset.x * static_cast<float>(currentSprite % maxNumbersOfSprites);
		currentSprite++;
		charBase_ptr->baseRect.left = xRecPos;
		charBase_ptr->baseRect.right = xRecPos + charBase_ptr->spriteOffset.x;
		charBase_ptr->baseRect.top = yRecPos;
		charBase_ptr->baseRect.bottom = yRecPos + charBase_ptr->spriteOffset.y;

		currentTime = 0.f;
		if (currentSprite >= maxNumbersOfSprites)
		{
			currentSprite = 0;
		}
	}

	////
}

void AnimationComponent::ChangeAnimation(const char* animName)
{
	if (DoesAnimationExist(animName))
	{
		return;
	}

	if(currentAnimation == animations[animName])
	{
		return;
	}

	currentAnimation = animations[animName];

	float xRecPos = 0.f;
	const float yRecPos = currentAnimation->yFrameRow * charBase_ptr->spriteOffset.y;

	charBase_ptr->baseRect.left = xRecPos;
	charBase_ptr->baseRect.right = xRecPos + charBase_ptr->spriteOffset.x;
	charBase_ptr->baseRect.top = yRecPos;
	charBase_ptr->baseRect.bottom = yRecPos + charBase_ptr->spriteOffset.y;
	currentSprite++;
}

bool AnimationComponent::DoesAnimationExist(const char* animName)
{
	return(animations.find(animName) == animations.end());
}

void AnimationComponent::AddAnimation(const char* key, Animation* anim)
{
	if (animations.find(key) == animations.end())
	{
		// If the animation with the given key does not exist, add it to the map
		animations[key] = anim;

		// If this is the first animation added, set it as the current animation
		if (animations.size() == 1)
		{
			currentAnimation = anim;
		}
	}
	else
	{
		// If an animation with the given key already exists, you can handle this case accordingly
		// For example, you could overwrite the existing animation or throw an error
		// Here, we are just printing a message to the console
		std::cout << "Animation with key '" << key << "' already exists." << std::endl;
	}
}

void AnimationComponent::CleanUp()
{
	// Iterate through the map and delete each animation
	for (auto& pair : animations)
	{
		delete pair.second;
	}

	// Clear the map
	animations.clear();
}

void AnimationComponent::LoadAnimation(const char* filePath)
{

	std::ifstream readFile(filePath);
	std::string spritSheet;

	std::string animationName;
	int numOfFrames;
	float animSpeed;
	int anim_Y_Row;
	

	if (readFile.is_open())
	{
		readFile >> spritSheet;
		readFile >> charBase_ptr->spriteOffset.x;
		readFile >> charBase_ptr->spriteOffset.y;

		while (readFile>> animationName >> numOfFrames >> animSpeed >> anim_Y_Row)
		{
			AddAnimation(animationName.c_str(), new Animation(numOfFrames, animSpeed, anim_Y_Row));
		}
	}
	readFile.close();
	charBase_ptr->spriteSheet = X::LoadTexture(spritSheet.c_str());
}
