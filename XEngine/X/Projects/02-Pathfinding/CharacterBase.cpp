#include "CharacterBase.h"
#include "AnimationComponent.h"

CharacterBase::CharacterBase()
{
    animationManager = new AnimationComponent(this);
}

CharacterBase::~CharacterBase()
{
    delete animationManager;
}

void CharacterBase::AddAnimation(const char* animKey, Animation* anim)
{
    if (animationManager == nullptr)
    {
        return;
    }
    animationManager->AddAnimation(animKey, anim);
}

void CharacterBase::Render()
{
    X::DrawSprite(spriteSheet, baseRect, pos);
}
