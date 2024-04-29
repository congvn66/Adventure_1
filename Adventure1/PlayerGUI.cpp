#include "stdafx.h"
#include "PlayerGUI.h"



PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;
	this->InitFont();
	this->InitHpBar();
	this->InitExpBar();
	this->InitLevel();
	this->InitPlayerTab(this->font, *this->player);
}
PlayerGUI::~PlayerGUI()
{
	delete this->playerTabs;
}

PlayerTabs* PlayerGUI::GetPlayerTabs()
{
	return this->playerTabs;
}

const bool PlayerGUI::GetTabsOpen() const
{
	return this->playerTabs->TabsOpened();
}

void PlayerGUI::ToggleCharacterTab()
{
	this->playerTabs->ToggleTab(PlayerTabsType::CHARACTER);
}



void PlayerGUI::InitFont()
{
	this->font.loadFromFile("Assets/Font/joystix monospace.otf");
}
void PlayerGUI::InitHpBar()
{
	float width = 300.f;
	float height = 40.f;
	float x = 20.f;
	float y = 20.f;
	this->hpBarMaxWidth = width;
	this->hpBarBack.setSize(Vector2f(width,height));
	this->hpBarBack.setFillColor(Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x,y);
	this->hpBarInner.setSize(Vector2f(width, height));
	this->hpBarInner.setFillColor(Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpText.setCharacterSize(22);
	this->hpText.setFont(this->font);
	this->hpText.setPosition(this->hpBarInner.getPosition().x+10.f, this->hpBarInner.getPosition().y+5.f);
}
void PlayerGUI::InitLevel()
{
	float width = 30.f;
	float height = 30.f;
	float x = this->expBarMaxWidth+width;
	float y = 60.f;
	this->levelBarBack.setSize(Vector2f(width, height));
	this->levelBarBack.setFillColor(Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelText.setCharacterSize(16);
	this->levelText.setFont(this->font);
	this->levelText.setPosition(this->levelBarBack.getPosition().x + 10.f, this->levelBarBack.getPosition().y + 5.f);
}
void PlayerGUI::InitExpBar()
{
	float width = 200.f;
	float height = 30.f;
	float x = 20.f;
	float y = 60.f;
	this->expBarMaxWidth = width;
	this->expBarBack.setSize(Vector2f(width, height));
	this->expBarBack.setFillColor(Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);
	this->expBarInner.setSize(Vector2f(width, height));
	this->expBarInner.setFillColor(Color(44, 127, 209, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expText.setCharacterSize(16);
	this->expText.setFont(this->font);
	this->expText.setPosition(this->expBarInner.getPosition().x + 10.f, this->expBarInner.getPosition().y + 5.f);
}
void PlayerGUI::InitPlayerTab(Font& font, Player& player)
{
	this->playerTabs = new PlayerTabs(font, player);
}
void PlayerGUI::Update(const float& dt, const Vector2i& mousePosWindow)
{
	this->UpdateHpBar();
	this->UpdateExpBar();
	this->UpdateLevelBar();
	this->UpdatePlayerTabs(mousePosWindow);
}
void PlayerGUI::UpdateExpBar()
{
	float percent = static_cast<float>(this->player->GetAttributeComponent()->exp) / static_cast<float>(this->player->GetAttributeComponent()->expNext);
	this->expBarInner.setSize(Vector2f(static_cast<float>(floor(this->expBarMaxWidth * percent)), this->expBarInner.getSize().y));

	this->expString = to_string(this->player->GetAttributeComponent()->exp) + "/" + to_string(this->player->GetAttributeComponent()->expNext);
	this->expText.setString(this->expString);
}
void PlayerGUI::UpdateHpBar()
{
	float percent = static_cast<float>(this->player->GetAttributeComponent()->hp) / static_cast<float>(this->player->GetAttributeComponent()->hpMax);
	this->hpBarInner.setSize(Vector2f(static_cast<float>(floor(this->hpBarMaxWidth * percent)), this->hpBarInner.getSize().y));

	this->hpString = to_string(this->player->GetAttributeComponent()->hp) + "/"+ to_string(this->player->GetAttributeComponent()->hpMax);
	this->hpText.setString(this->hpString);
}
void PlayerGUI::UpdateLevelBar()
{
	this->levelString = to_string(this->player->GetAttributeComponent()->level);
	this->levelText.setString(this->levelString);
}
void PlayerGUI::UpdatePlayerTabs(const Vector2i& mousePosWindow)
{
	this->playerTabs->Update(mousePosWindow);
}
void PlayerGUI::RenderLevelBar(RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelText);
}
void PlayerGUI::RenderExpBar(RenderTarget& target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expText);
}
void PlayerGUI::RenderHpBar(RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpText);
}
void PlayerGUI::RenderPlayerTabs(RenderTarget& target)
{
	this->playerTabs->Render(target);
}
void PlayerGUI::Render(RenderTarget& target)
{
	this->RenderLevelBar(target);
	this->RenderHpBar(target);
	this->RenderExpBar(target);
	this->RenderPlayerTabs(target);
}
