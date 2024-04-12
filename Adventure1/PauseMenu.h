#pragma once

#include "Gui.h"

using namespace sf;

class PauseMenu
{
private:
	RectangleShape background;
	RectangleShape container;
	Font& font;
	Text text;

	map<string, gui::Button*> buttons;
public:
	PauseMenu(RenderWindow& window,Font& font);
	~PauseMenu();

	map<string, gui::Button*>& GetButton();

	const bool IsButtonPressed(const string key);

	void AddButton(const string key,float y, const string text);
	void Update(const Vector2i& mousePosWindow);
	void Render(RenderTarget& target);
};

