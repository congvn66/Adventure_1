#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{//sword
	if (this->weaponTexture.loadFromFile("Assets/Player/Texture/pixswords.png"))
	{
		cout << "GameState: sword is ready!" << endl;
	}
	this->weaponSprite.setTexture(weaponTexture);
	this->weaponSprite.setScale(1.f, 1.f);
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

	const float PI = 3.14159625;
	float deg = atan2(dY, dX) * 180 / PI;

	this->weaponSprite.setRotation(deg + 90.f);
}

void Sword::Render(RenderTarget& target)
{
	target.draw(this->weaponSprite);
}
