#pragma once

#include "Tab.h"

class CharacterTab : public Tab
{
private:
	RectangleShape tabBack;
	Text info;

	void InitText();
public:
	CharacterTab(Font& font, Player& player);
	~CharacterTab();

	void Update();
	void Render(RenderTarget& target);
};

