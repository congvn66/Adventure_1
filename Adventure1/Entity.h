#pragma once
//now i know its not enemy :D

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

using namespace std;
using namespace sf;


using namespace sf;

class Entity
{
private:
	void InitVal();

protected:
	HitboxComponent* hitboxComponent;
	Sprite sprite;//now every entity has a sprite
	MovementComponent* movementComponent;// move 
	AnimationComponent* animationComponent;//animate
public:
	//con & de
	Entity();
	~Entity();

	//it is w it is
	void CreateHitboxComponent(Sprite& sprite, float offsetX, float offsetY, float width, float height);
	void CreateMovementComponent(const float maxSpeed, const float acceleration, 
		const float deceleration);
	void CreateAnimationComponent(Texture& textureSheet);
	virtual void SetPos(const float x, const float y);
	virtual void Move(const float& deltaTime, const float dirX, const float dirY);
	virtual void Update(const float& deltaTime);
	virtual void Render(RenderTarget& target);

	//texture 4 each entity
	void SetTexture(Texture& texture);
};

