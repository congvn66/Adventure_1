#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <stack>
#include <map>

using namespace std;
using namespace sf;

class AnimationComponent
{
private:
	//Animation
	class Animation {
	public:
		Sprite& sprite;
		Texture& textureSheet;
		float speed;
		float timer;
		float animationTimer;
		int width;
		int height;
		bool done;
		IntRect startRect;
		IntRect endRect;
		IntRect curRect;

		Animation(Sprite& sprite,Texture& textureSheet, float animationTimer, 
			int startFrameX, int startFrameY, int frameOnX, int frameOnY, int width, int height)
			:sprite(sprite),textureSheet(textureSheet), animationTimer(animationTimer), 
			width(width), height(height)
		{
			//fuk too complex
			this->timer = 0.f;
			done = false;

			//dis one same with mufasa shibai taught
			this->startRect = IntRect(startFrameX*width, startFrameY*height, width, height);
			this->curRect = this->startRect;
			this->endRect = IntRect(frameOnX*width, frameOnY*height, width, height);
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
			this->sprite.setScale(Vector2f(4, 4));
		}
		const bool& Play(const float& dt) {
			this->done = false;
			//update timer
			this->timer += 500.f * dt;
			if (this->timer > this->animationTimer) {
				//reset
				this->timer = 0.f;


				//animate
				if (this->curRect != this->endRect) {
					this->curRect.left += this->width;
				}
				//reset
				else {
					this->curRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->curRect);
			}
			return this->done;
		}
		const bool& Play(const float& dt, float mod_percent) {
			//update timer
			this -> done = false;
			if (mod_percent < 0.5f) {
				mod_percent = 0.5f;
			}
			this->timer +=mod_percent*500.f * dt;
			if (this->timer > this->animationTimer) {
				//reset
				this->timer = 0.f;


				//animate
				if (this->curRect != this->endRect) {
					this->curRect.left += this->width;
				}
				//reset
				else {
					this->curRect.left = this->startRect.left;
					this->done = true;
				}
				this->sprite.setTextureRect(this->curRect);
			}
			return this->done;
		}
		void Reset() {
			this->timer = this->animationTimer;
			this->curRect = this->startRect;
		}
		const bool& IsDone() const {
			return this->done;
		}
	};
	Sprite& sprite;
	Texture& textureSheet;
	map <string, Animation*> animation;
	Animation* lastAnimation;
	Animation* priorityAnimation;
public:
	AnimationComponent(Sprite& sprite, Texture& textureSheet);
	~AnimationComponent();

	const bool& IsDone(const string name);

	void AddAnimation(const string name, float animationTimer,
		int startFrameX, int startFrameY, int frameOnX, int frameOnY, int width, int height);
	
	void Play(const string name,const float& dt, const bool prior = false);
	void Play(const string name, const float& dt, const float& modifier, const float& modifier_max, const bool prior = false);
};

