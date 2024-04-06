#include "stdafx.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(RenderWindow& window, Font& font)
	:font(font)
{
	this->background.setSize(Vector2f(static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));
	this->background.setFillColor(Color(20,20,20,100));

	this->container.setSize(Vector2f(static_cast<float>(window.getSize().x)/4.f,
		static_cast<float>(window.getSize().y)));
	this->container.setFillColor(Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x)/2.f-this->container.getSize().x/2.f, 0.f);

	this->text.setFont(font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(72);
	this->text.setString("PAUSED");
	this->text.setPosition(this->container.getPosition().x+this->container.getSize().x/2.f-this->text.getGlobalBounds().width/2.f,
		this->container.getPosition().y);
}

PauseMenu::~PauseMenu()
{
	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

map<string, gui::Button*>& PauseMenu::GetButton()
{
	// TODO: insert return statement here
	return this->buttons;
}

const bool PauseMenu::IsButtonPressed(const string key) 
{
	// TODO: insert return statement here
	return this->buttons[key]->IsPressed();
}

void PauseMenu::AddButton(const string key, float y, const string text)
{
	float width = 120.f;
	float height = 60.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
	this->buttons[key] = new gui::Button(x, y, width, height,
		&this->font, text, Color::Transparent, Color::Transparent, Color::Transparent, Color::White, Color::Yellow, Color::Yellow);
}

void PauseMenu::Update(const Vector2f& mousePos)
{
	for (auto& i : this->buttons) {
		i.second->Update(mousePos);
	}
}

void PauseMenu::Render(RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	for (auto& i : this->buttons) {
		i.second->Render(target);
	}
	target.draw(this->text);
}
