#pragma once

#include "Button.h"

using namespace sf;

class PauseMenu
{
private:
	RectangleShape background;
	RectangleShape container;
	Font& font;
	Text text;

	map<string, Button*> buttons;
public:
	PauseMenu(RenderWindow& window,Font& font);
	~PauseMenu();

	map<string, Button*>& GetButton();

	const bool IsButtonPressed(const string key);

	void AddButton(const string key,float y, const string text);
	void Update(const Vector2f& mousePos);
	void Render(RenderTarget& target);
};

