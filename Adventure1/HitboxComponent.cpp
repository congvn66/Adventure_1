#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offsetX, 
	float offsetY, float width, float height)
	:sprite(sprite), offsetX(offsetX), offsetY(offsetY)
{
	//next pos init
	this->nextPos.left = 0.f;
	this->nextPos.top = 0.f;
	this->nextPos.height = height;
	this->nextPos.width = width;

	//hitbox
	this->hitbox.setPosition(this->sprite.getPosition().x+offsetX, this->sprite.getPosition().y + offsetY);
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(Color::Green);

}

HitboxComponent::~HitboxComponent()
{
}

const FloatRect& HitboxComponent::GetNextPos(const Vector2f& velocity)
{
	this->nextPos.left = this->hitbox.getPosition().x + velocity.x; // x axis
	this->nextPos.top = this->hitbox.getPosition().y + velocity.y; // y axis
	return this->nextPos;
}

const Vector2f& HitboxComponent::GetPosition() const
{
	//cout <<"hitbox:" << this->hitbox.getPosition().x << " " << this->hitbox.getPosition().y << endl;
	return this->hitbox.getPosition();
}

const FloatRect HitboxComponent::GetGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}
void HitboxComponent::SetPosition(Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::SetPosition(const float x, const float y)
{
	this->hitbox.setPosition(x,y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

bool HitboxComponent::Intersect(const FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::Update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::Render(RenderTarget& target)
{
	target.draw(this->hitbox);
}
