#pragma once
#include "Player.h"
#include "Gui.h"
class Tab
{
protected:
	Font& font;
	Player& player;
	bool hidden;
public:
	Tab(Font& font,Player& player,bool hidden);
	~Tab();
	const bool& GetHidden() const;
	const bool& GetOpen() const;
	void Toggle();
	void Hide();
	void Show();
	virtual void Update() = 0;
	virtual void Render(RenderTarget& target) = 0;
};

