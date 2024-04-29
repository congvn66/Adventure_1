#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned dmgMin, unsigned dmgMax, unsigned range, unsigned level,unsigned value, string texFile)
	:Melee(dmgMin, dmgMax, range,level, value, texFile)
{//sword
	
	this->weaponSprite.setOrigin(this->weaponSprite.getGlobalBounds().width / 2.f, this->weaponSprite.getGlobalBounds().height);
}

Sword::~Sword()
{
}

void Sword::Update(const Vector2f centerPos, const Vector2f& mousePosView)
{
	this->weaponSprite.setPosition(centerPos);
	float dX = mousePosView.x - this->weaponSprite.getPosition().x;
	float dY = mousePosView.y - this->weaponSprite.getPosition().y;

	const float PI = 3.14159625f;
	float deg = atan2(dY, dX) * 180.f / PI;

	//this->weaponSprite.setRotation(deg + 90.f);

	if (this->atkTimer.getElapsedTime().asMilliseconds() < this->atkTimerMax/4)
	{
		float len = sqrt(pow(dX, 2) + pow(dY, 2));
		Vector2f normVec(dX / len, dY / len);
		this->weaponSprite.setPosition(centerPos.x + normVec.x * 20.f, centerPos.y + normVec.y * 20.f);
	}
	else
	{
		this->weaponSprite.setRotation(deg + 90.f);
	}
}

void Sword::Render(RenderTarget& target)
{
	target.draw(this->weaponSprite);
}

Sword* Sword::clone()
{
	return new Sword(*this); //copy of it
}
