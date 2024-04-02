#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(Vector2f(30.0f,30.0f));
	this->movementSpeed = 100.0f;
}

Entity::~Entity()
{
}

void Entity::Move(const float& deltaTime,const float dirX, const float dirY)
{
	this->shape.move(dirX*this->movementSpeed*deltaTime, dirY*this->movementSpeed*deltaTime);
}

void Entity::Update(const float& deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		this->Move(deltaTime, -2.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		this->Move(deltaTime, 2.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		this->Move(deltaTime, 0.0f, -2.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		this->Move(deltaTime, 0.0f, 2.0f);
	}
}

void Entity::Render(RenderTarget* target)
{
	target->draw(this->shape);
}
