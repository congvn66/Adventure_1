#pragma once

enum MovingState {IDLE=0,M,M_LEFT,M_RIGHT,M_UP,M_DOWN};

class MovementComponent
{
private:
	Sprite& sprite;	
	float maxSpeed;
	float acceleration;
	float deceleration;
	Vector2f velocity;


public:
	MovementComponent(float maxSpeed, Sprite& sprite, float acceleration, float decelaration);
	~MovementComponent();

	const float& GetMaxSpeed() const;
	const Vector2f& GetVelocity() const;

	const bool GetState(const short unsigned state) const;

	void Move(const float dirX, const float dirY, const float& dt);
	void Update(const float& dt);
};

