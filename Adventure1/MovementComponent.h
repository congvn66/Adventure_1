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

using namespace sf;

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

	const Vector2f& GetVelocity() const;

	void Move(const float dirX, const float dirY, const float& dt);
	void Update(const float& dt);
};

