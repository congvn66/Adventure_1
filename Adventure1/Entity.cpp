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
	delete this->attributeComponent;
}

void Entity::InitVal()
{
	this->movementComponent = nullptr;
	this->animationComponent = nullptr;
	this->hitboxComponent = nullptr;
}
const FloatRect Entity::GetNextPosBounds(const float& deltaTime) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->GetNextPos(this->movementComponent->GetVelocity()*deltaTime);
	}
	return FloatRect(-1.f, -1.f,-1.f,-1.f);
}
const Vector2i Entity::getGridPos(const int gridSizeI) const
{
	if (this->hitboxComponent) {
		return Vector2i(static_cast<int>(this->hitboxComponent->GetPosition().x)/gridSizeI,
				static_cast<int>(this->hitboxComponent->GetPosition().y) / gridSizeI);
	}
	return Vector2i(static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI);
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
const Vector2f Entity::GetCenterPos() const
{
	if (this->hitboxComponent) {
		return this->hitboxComponent->GetPosition()+ Vector2f(this->hitboxComponent->GetGlobalBounds().width/2.f,this->hitboxComponent->GetGlobalBounds().height/2.f);
	}
	return this->sprite.getPosition()+ Vector2f(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
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
void Entity::CreateAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}
void Entity::SetTexture(Texture& texture)
{
	this->sprite.setTexture(texture);
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
void Entity::Update(const float& deltaTime, Vector2f& mousePosView)
{

}
void Entity::Render(RenderTarget& target,Shader* shader, const bool showHitbox)
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
