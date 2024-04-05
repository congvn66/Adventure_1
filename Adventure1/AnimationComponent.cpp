#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{
	this->lastAnimation = nullptr;
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animation) {
		delete i.second;
	}
}

void AnimationComponent::AddAnimation(const string name, float animationTimer,
	int startFrameX, int startFrameY, int frameOnX, int frameOnY, int width, int height)
{
	this->animation[name] = new Animation(this->sprite, this->textureSheet, animationTimer
		, startFrameX, startFrameY, frameOnX, frameOnY, width, height);
}


void AnimationComponent::Play(const string name, const float& dt)
{
	//i even cant realise the diffirent :D
	if (this->lastAnimation != this->animation[name]) {
		if (this->lastAnimation == nullptr) {
			this->lastAnimation = this->animation[name];
		}
		else {
			this->lastAnimation->Reset();
			this->lastAnimation = this->animation[name];
		}
	}
	this->animation[name]->Play(dt);
}
