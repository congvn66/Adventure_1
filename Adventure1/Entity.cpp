#include "Entity.h"

void Entity::InitVal()
{
	this->sprite = nullptr;
	this->texture = nullptr;
	this->movementSpeed = 100.0f;
}

Entity::Entity()
{
	this->InitVal();
}

Entity::~Entity()
{
	delete this->sprite;
}

void Entity::CreateSprite(Texture* texture)
{
	this->texture = texture;
	this->sprite->setTexture(*this->texture);
}

void Entity::Move(const float& deltaTime,const float dirX, const float dirY)
{
	if (this->sprite != nullptr) {
		this->sprite->move(dirX * this->movementSpeed * deltaTime, dirY * this->movementSpeed * deltaTime);
	}
	
}

void Entity::Update(const float& deltaTime)
{
	
}

void Entity::Render(RenderTarget* target)
{
	if (this->sprite) {
		target->draw(*this->sprite);
	}
}
