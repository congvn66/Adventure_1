#include "Entity.h"

void Entity::InitVal()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
}

Entity::Entity()
{
	this->InitVal();
}

Entity::~Entity()
{
	delete this->movementComponent; 
	delete this->animationComponent;
}

void Entity::CreateMovementComponent(const float maxSpeed,const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(maxSpeed, this->sprite,acceleration,deceleration);
}

void Entity::CreateAnimationComponent(Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::SetTexture(Texture& texture)
{
	this->sprite.setTexture(texture);
	this->sprite.scale(Vector2f(4, 4));
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

}

void Entity::Render(RenderTarget* target)
{
	
	target->draw(this->sprite);

}
