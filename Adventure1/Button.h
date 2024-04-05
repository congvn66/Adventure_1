#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

enum ButtonStates{B_IDLE =0, B_HOVER, B_ACTIVATED};

class Button
{
private:
	//state
	short unsigned buttonState;
	bool pressed;
	bool hover;

	//elements
	RectangleShape shape;
	Font* font;
	Text text;
	Color idleColor;
	Color hoverColor;
	Color activeColor;
public:
	//constructor, deconstructor
	Button(float x, float y, float width, float height,Font* font, 
		string text,Color idleColor, Color hoverColor,Color activeColor);
	~Button();
	
	//look in cpp file
	const bool IsPressed() const;
	void Update(const Vector2f mousePos);
	void Render(RenderTarget& target);
};

