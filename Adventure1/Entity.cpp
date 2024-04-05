#include "Entity.h"

void Entity::InitVal()
{
	this->movementComponent = nullptr;
}

Entity::Entity()
{
	this->InitVal();
}

Entity::~Entity()
{
	delete this->movementComponent;
}

void Entity::CreateMovementComponent(const float maxSpeed,const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(maxSpeed, this->sprite,acceleration,deceleration);
}

void Entity::SetTexture(Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::SetPos(const float x, const float y)
{
	this->sprite.setPosition(x,y);
}

void Entity::Move(const float& deltaTime,const float dirX, const float dirY)
{
	if (this->movementComponent!=nullptr) {
		this->movementComponent->Move(dirX, dirY,deltaTime);// set velocity
	}
	
}

void Entity::Update(const float& deltaTime)
{
	if (this->movementComponent) {
		this->movementComponent->Update(deltaTime);
	}
}

void Entity::Render(RenderTarget* target)
{
	
	target->draw(this->sprite);

}
