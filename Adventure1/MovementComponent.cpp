#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(float maxSpeed, Sprite& sprite,
	float acceleration, float decelaration)
	:sprite(sprite), maxSpeed(maxSpeed), acceleration(acceleration), deceleration(decelaration)
{
}

MovementComponent::~MovementComponent()
{
}

const float& MovementComponent::GetMaxSpeed() const
{
	// TODO: insert return statement here
	return this->maxSpeed;
}

const Vector2f& MovementComponent::GetVelocity() const
{
	// TODO: insert return statement here
	return this->velocity;
}

const bool MovementComponent::GetState(const short unsigned state) const
{
	switch (state) {
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f) {
			return true;
		}
		break;
	case M:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f) {
			return true;
		}
		break;
	case M_LEFT:
		if (this->velocity.x < 0.f) {
			return true;
		}
		break;
	case M_RIGHT:
		if (this->velocity.x > 0.f) {
			return true;
		}
		break;
	case M_DOWN:
		if (this->velocity.y > 0.f) {
			return true;
		}
		break;
	case M_UP:
		if (this->velocity.y < 0.f) {
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}

void MovementComponent::Move(const float dirX, const float dirY, const float& dt)
{
	//acceleration
	this->velocity.x += this->acceleration * dirX;
	this->velocity.y += this->acceleration * dirY;
}

void MovementComponent::Update(const float& dt)
{
	if (this->velocity.x > 0.f) { //right
		//check for surpassing max speed
		if (this->velocity.x > this->maxSpeed) {
			this->velocity.x = this->maxSpeed;
		}
		//deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f) {
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0.f) { //left
		//check for surpassing max speed
		if (this->velocity.x < -this->maxSpeed) {
			this->velocity.x = -this->maxSpeed;
		}
		//deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f) {
			this->velocity.x = 0.f;
		}
	}
	if (this->velocity.y > 0.f) { //down
		//check for surpassing max speed
		if (this->velocity.y > this->maxSpeed) {
			this->velocity.y = this->maxSpeed;
		}
		//deceleration
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f) {
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0.f) { //up
		//check for surpassing max speed
		if (this->velocity.y < -this->maxSpeed) {
			this->velocity.y = -this->maxSpeed;
		}
		//deceleration
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f) {
			this->velocity.y = 0.f;
		}
	}
	//final
	this->sprite.move(this->velocity * dt);
}
