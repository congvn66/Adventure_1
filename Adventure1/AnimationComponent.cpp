#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Sprite& sprite, Texture& textureSheet)
	:sprite(sprite), textureSheet(textureSheet)
{
	this->lastAnimation = nullptr;
	this->priorityAnimation = nullptr;
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animation) {
		delete i.second;
	}
}

const bool& AnimationComponent::IsDone( const string name)
{
	// TODO: insert return statement here
	return this->animation[name]->IsDone();
}

void AnimationComponent::AddAnimation(const string name, float animationTimer,
	int startFrameX, int startFrameY, int frameOnX, int frameOnY, int width, int height)
{
	this->animation[name] = new Animation(this->sprite, this->textureSheet, animationTimer
		, startFrameX, startFrameY, frameOnX, frameOnY, width, height);
}


void AnimationComponent::Play(const string name, const float& dt, const bool prior)
{
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animation[name]) {
			if (this->lastAnimation != this->animation[name]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animation[name];
				}
				else {
					this->lastAnimation->Reset();
					this->lastAnimation = this->animation[name];
				}
			}
			if (this->animation[name]->Play(dt)) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else {
		if (prior) {
			this->priorityAnimation = this->animation[name];
		}
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
	
}

void AnimationComponent::Play(const string name, const float& dt, const float& modifier, 
	const float& modifier_max, const bool prior)
{
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animation[name]) {
			if (this->lastAnimation != this->animation[name]) {
				if (this->lastAnimation == nullptr) {
					this->lastAnimation = this->animation[name];
				}
				else {
					this->lastAnimation->Reset();
					this->lastAnimation = this->animation[name];
				}
			}
			if (this->animation[name]->Play(dt, abs(modifier / modifier_max))) {
				this->priorityAnimation = nullptr;
			}
		}
	}
	else {
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
		this->animation[name]->Play(dt,abs(modifier/modifier_max));
	}
}
