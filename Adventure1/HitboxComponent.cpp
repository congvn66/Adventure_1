#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(Sprite& sprite, float offsetX, 
	float offsetY, float width, float height)
	:sprite(sprite), offsetX(offsetX), offsetY(offsetY)
{
	this->hitbox.setPosition(this->sprite.getPosition().x+offsetX, this->sprite.getPosition().y + offsetY);
	this->hitbox.setSize(Vector2f(width, height));
	this->hitbox.setFillColor(Color::Transparent);
	this->hitbox.setOutlineThickness(1.0f);
	this->hitbox.setOutlineColor(Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::CheckIntersect(const FloatRect& frect)
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
