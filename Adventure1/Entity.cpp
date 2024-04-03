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
	
}

void Entity::Render(RenderTarget* target)
{
	target->draw(this->shape);
}
