#pragma once
//now i know its not enemy :D

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <stack>
#include <map>

using namespace std;
using namespace sf;


using namespace sf;

class Entity
{
protected:
	RectangleShape shape;
	float movementSpeed;
public:
	Entity();
	~Entity();

	virtual void Move(const float& deltaTime, const float dirX, const float dirY);
	virtual void Update(const float& deltaTime);
	virtual void Render(RenderTarget* target);
};

