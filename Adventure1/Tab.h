#pragma once
#include "Player.h"
#include "Gui.h"
class Tab
{
protected:
	Font& font;
	Player& player;
	bool hidden;
	RectangleShape container;

	map<string, gui::Button*> buttons;
public:
	Tab(Font& font,Player& player,bool hidden);
	~Tab();
	const bool& GetHidden() const;
	const bool& GetOpen() const;
	map<string, gui::Button*>& GetButton();
	const bool IsButtonPressed(const string key);
	void AddButton(const string key, float y, const string text);
	void Toggle();
	void Hide();
	void Show();
	virtual void Update(const Vector2i& mousePosWindow) = 0;
	virtual void Render(RenderTarget& target) = 0;
};

