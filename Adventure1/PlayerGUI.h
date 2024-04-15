#pragma once

#include "Player.h"

class PlayerGUI
{
private:
	Player* player;
	Font font;

	//level
	Text levelText;
	string levelString;
	RectangleShape levelBarBack;

	//exp bar
	Text expText;
	string expString;
	float expBarMaxWidth;
	RectangleShape expBarBack;
	RectangleShape expBarInner; //actual exp

	//hp bar
	Text hpText;
	string hpString;
	float hpBarMaxWidth;
	RectangleShape hpBarBack;
	RectangleShape hpBarInner; //actual health

	void InitFont();
	void InitHpBar();
	void InitLevel();
	void InitExpBar();
public:
	PlayerGUI(Player* player);
	~PlayerGUI();

	void Update(const float& dt);
	void UpdateExpBar();
	void UpdateHpBar();
	void UpdateLevelBar();

	void RenderLevelBar(RenderTarget& target);
	void RenderExpBar(RenderTarget& target);
	void RenderHpBar(RenderTarget& target);
	void Render(RenderTarget& target);
};

