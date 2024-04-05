#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class HitboxComponent
{
private:
	Sprite& sprite;
	RectangleShape hitbox;
	float offsetX;
	float offsetY;
public:
	HitboxComponent(Sprite& sprite, float offsetX,float offsetY, float width, float height);
	~HitboxComponent();

	bool CheckIntersect(const FloatRect& frect);
	void Update();
	void Render(RenderTarget& target);
};

