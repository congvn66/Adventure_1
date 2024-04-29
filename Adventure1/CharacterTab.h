#pragma once

#include "Tab.h"
#include "Gui.h"

class CharacterTab : public Tab
{
private:
	RectangleShape tabBack;
	Text info;
	

	void InitText();
public:
	CharacterTab(Font& font, Player& player);
	~CharacterTab();

	void Update(const Vector2i& mousePosWindow);
	void Render(RenderTarget& target);
};

