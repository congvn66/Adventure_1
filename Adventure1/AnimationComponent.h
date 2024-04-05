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

			//dis one same with mufasa shibai taught
			this->startRect = IntRect(startFrameX*width, startFrameY*height, width, height);
			this->curRect = this->startRect;
			this->endRect = IntRect(frameOnX*width, frameOnY*height, width, height);
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
			this->sprite.setScale(Vector2f(4, 4));
		}

		void Play(const float& dt) {
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
				}
				this->sprite.setTextureRect(this->curRect);
			}
		}
		void Reset() {
			this->timer = 0.f;
			this->curRect = this->startRect;
		}
	};
	Sprite& sprite;
	Texture& textureSheet;
	map <string, Animation*> animation;
	Animation* lastAnimation;
public:
	AnimationComponent(Sprite& sprite, Texture& textureSheet);
	~AnimationComponent();

	void AddAnimation(const string name, float animationTimer,
		int startFrameX, int startFrameY, int frameOnX, int frameOnY, int width, int height);
	
	void Play(const string name,const float& dt);
};

