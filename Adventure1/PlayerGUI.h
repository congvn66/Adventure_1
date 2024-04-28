#pragma once

#include "PlayerTabs.h"

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

	PlayerTabs* playerTabs;

	void InitFont();
	void InitHpBar();
	void InitLevel();
	void InitExpBar();
	void InitPlayerTab(Font& font,Player& player);
public:
	PlayerGUI(Player* player);
	~PlayerGUI();

	const bool GetTabsOpen() const;
	void ToggleCharacterTab();

	void Update(const float& dt);
	void UpdateExpBar();
	void UpdateHpBar();
	void UpdateLevelBar();
	void UpdatePlayerTabs();

	void RenderLevelBar(RenderTarget& target);
	void RenderExpBar(RenderTarget& target);
	void RenderHpBar(RenderTarget& target);
	void RenderPlayerTabs(RenderTarget& target);
	void Render(RenderTarget& target);
};

