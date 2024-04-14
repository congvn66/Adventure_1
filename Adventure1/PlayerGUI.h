#pragma once

#include "Player.h"

class PlayerGUI
{
private:
	Player* player;
	Font font;

	//hp bar
	Text hpText;
	string hpString;
	float hpBarMaxWidth;
	RectangleShape hpBarBack;
	RectangleShape hpBarInner; //actual health

	void InitFont();
	void InitHpBar();
public:
	PlayerGUI(Player* player);
	~PlayerGUI();

	void Update(const float& dt);
	void UpdateHpBar();
	void RenderHpBar(RenderTarget& target);
	void Render(RenderTarget& target);
};

