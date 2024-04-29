#include "stdafx.h"
#include "Tab.h"

Tab::Tab(Font& font, Player& player, bool hidden)
	:font(font), player(player), hidden(hidden)
{

	this->container.setSize(Vector2f(static_cast<float>(1920) / 4.f,
		static_cast<float>(1080)));
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(1920) / 2.f - this->container.getSize().x / 2.f, 0.f);
}

Tab::~Tab()
{
	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

const bool& Tab::GetHidden() const
{
	// TODO: insert return statement here
	return this->hidden;
}

const bool& Tab::GetOpen() const
{
	// TODO: insert return statement here
	return (this->hidden==false);
}

map<string, gui::Button*>& Tab::GetButton()
{
	// TODO: insert return statement here
	return this->buttons;
}

const bool Tab::IsButtonPressed(const string key)
{
	return this->buttons[key]->IsPressed();
}

void Tab::AddButton(const string key, float y, const string text)
{
	float width = 120.f;
	float height = 60.f;
	float x = 150.f;
	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, Color::Transparent, Color::Transparent, Color::Transparent, Color::Yellow, Color::White, Color::Red);
}

void Tab::Toggle()
{
	if (this->hidden)
	{
		this->hidden = false;
	}
	else
	{
		this->hidden = true;
	}
}

void Tab::Hide()
{
	this->hidden = true;
}

void Tab::Show()
{
	this->hidden = false;
}
