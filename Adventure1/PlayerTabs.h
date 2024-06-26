#pragma once
#include "Player.h"
#include "Gui.h"
#include "CharacterTab.h"

enum PlayerTabsType {CHARACTER = 0, INVENTORY};

class PlayerTabs
{
private:
	vector<Tab*> tabs;
	
	Clock keyTimer;
	float keyTimeMax;

	Font& font;
	Player& player;
	void InitKeyTime();
	void InitTabs();
public:
	PlayerTabs(Font& font, Player& player);
	~PlayerTabs();

	bool GetKeyTime();
	const bool TabsOpened();

	Tab* GetCharTab();
	void ToggleTab(const int tabIndex);
	void Update(const Vector2i& mousePosWindow);
	void Render(RenderTarget& target);
};

