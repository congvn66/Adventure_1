#pragma once
//now i know its not enemy :D

#include "MovementComponent.h"

using namespace std;
using namespace sf;


using namespace sf;

class Entity
{
private:
	void InitVal();

protected:
	Sprite sprite;//now every entity has a sprite
	MovementComponent* movementComponent;
public:
	Entity();
	~Entity();
	void CreateMovementComponent(const float maxSpeed, const float acceleration, const float deceleration);
	void SetTexture(Texture& texture);
	virtual void SetPos(const float x, const float y);
	virtual void Move(const float& deltaTime, const float dirX, const float dirY);
	virtual void Update(const float& deltaTime);
	virtual void Render(RenderTarget* target);
};

