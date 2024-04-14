#include "stdafx.h"
#include "PlayerGUI.h"



PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;
	this->InitFont();
	this->InitHpBar();
}
PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::InitFont()
{
	this->font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF");
}
void PlayerGUI::InitHpBar()
{
	float width = 300.f;
	float height = 50.f;
	float x = 20.f;
	float y = 20.f;
	this->hpBarMaxWidth = width;
	this->hpBarBack.setSize(Vector2f(width,height));
	this->hpBarBack.setFillColor(Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x,y);
	this->hpBarInner.setSize(Vector2f(width, height));
	this->hpBarInner.setFillColor(Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpText.setFont(this->font);
	this->hpText.setPosition(this->hpBarInner.getPosition().x+10.f, this->hpBarInner.getPosition().y+5.f);
}
void PlayerGUI::Update(const float& dt)
{
	this->UpdateHpBar();
}
void PlayerGUI::UpdateHpBar()
{
	float percent = static_cast<float>(this->player->GetAttributeComponent()->hp) / static_cast<float>(this->player->GetAttributeComponent()->hpMax);
	this->hpBarInner.setSize(Vector2f(static_cast<float>(floor(this->hpBarMaxWidth * percent)), this->hpBarInner.getSize().y));

	this->hpString = to_string(this->player->GetAttributeComponent()->hp) + " on "+ to_string(this->player->GetAttributeComponent()->hpMax);
	this->hpText.setString(this->hpString);
}
void PlayerGUI::RenderHpBar(RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpText);
}
void PlayerGUI::Render(RenderTarget& target)
{
	this->RenderHpBar(target);
}
