#include "stdafx.h"
#include "CharacterTab.h"

void CharacterTab::InitText()
{
	//text
	this->info.setFont(this->font);
	this->info.setCharacterSize(30);
	this->info.setFillColor(Color(200,200,200,240));
	this->info.setPosition(this->tabBack.getPosition().x + 20.f, this->tabBack.getPosition().y + 20.f);
	this->info.setString(this->player.ToStringCharTab());
}

CharacterTab::CharacterTab(Font& font, Player& player)
	:Tab(font, player, false)
{
	//background
	this->tabBack.setFillColor(Color(20, 20, 20, 250));
	this->tabBack.setSize(Vector2f(900.f, 1080.f));
	

	this->InitText();
}

CharacterTab::~CharacterTab()
{
}

void CharacterTab::Update()
{
	if (!this->hidden)
	{
		this->info.setString(this->player.ToStringCharTab());
	}
}

void CharacterTab::Render(RenderTarget& target)
{
	if (!this->hidden)
	{
		target.draw(this->tabBack);
		target.draw(this->info);
	}
}

