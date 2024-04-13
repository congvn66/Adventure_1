#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
	this->InitVal();
}
Entity::~Entity()
{
	delete this->movementComponent; 
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Entity::InitVal()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}
const FloatRect& Entity::GetNextPosBounds(const float& deltaTime) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->GetNextPos(this->movementComponent->GetVelocity()*deltaTime);
	}
	return FloatRect();
}
const Vector2u Entity::getGridPos(const unsigned gridSizeU) const
{
	if (this->hitboxComponent) {
		return Vector2u(static_cast<unsigned>(this->hitboxComponent->GetPosition().x)/gridSizeU,
				static_cast<unsigned>(this->hitboxComponent->GetPosition().y) / gridSizeU);
	}
	return Vector2u(static_cast<unsigned>(this->sprite.getPosition().x) / gridSizeU,
		static_cast<unsigned>(this->sprite.getPosition().y) / gridSizeU);
}
const FloatRect Entity::GetGlobalBounds() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->GetGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}
const Vector2f& Entity::GetPos() const
{
	if (this->hitboxComponent) {
		return this->hitboxComponent->GetPosition();
	}
	return this->sprite.getPosition();
}
void Entity::CreateHitboxComponent(Sprite& sprite, float offsetX, float offsetY, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offsetX, offsetY,width, height);
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
	if (this->hitboxComponent) {
		this->hitboxComponent->SetPosition(x,y);
	}
	else
	{
		this->sprite.setPosition(x,y);
	}
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
void Entity::Render(RenderTarget& target)
{
	
}
void Entity::Stop()
{
	if (this->movementComponent)
	{
		this->movementComponent->Stop();
	}
}
void Entity::StopX()
{
	if (this->movementComponent)
	{
		this->movementComponent->StopX();
	}
}
void Entity::StopY()
{
	if (this->movementComponent)
	{
		this->movementComponent->StopY();
	}
}
