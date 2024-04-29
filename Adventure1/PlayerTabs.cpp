#include "stdafx.h"
#include "PlayerTabs.h"

void PlayerTabs::InitKeyTime()
{
	this->keyTimeMax = 0.2f;
	this->keyTimer.restart();
}

void PlayerTabs::InitTabs()
{
	this->tabs.push_back(new CharacterTab(font, player));
}

PlayerTabs::PlayerTabs(Font& font, Player& player)
	:font(font), player(player)
{
	this->InitTabs();
	this->InitKeyTime();
}

PlayerTabs::~PlayerTabs()
{
}

bool PlayerTabs::GetKeyTime()
{
	if (this->keyTimer.getElapsedTime().asSeconds() >= this->keyTimeMax) // the time has passed the limit
	{
		this->keyTimer.restart();
		return true;
	}
	return false;
}

const bool PlayerTabs::TabsOpened()
{
	bool open = false;
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->GetOpen())
		{
			open = true;
			break;
		}
	}
	return open;
}

void PlayerTabs::ToggleTab(const int tabIndex)
{
	if (tabIndex >= 0 && tabIndex < this->tabs.size())
	{
		this->tabs[tabIndex]->Toggle();
	}
}

void PlayerTabs::Update(const Vector2i& mousePosWindow)
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->GetOpen())
		{
			this->tabs[i]->Update(mousePosWindow);
			if (this->player.GetAC()->attributePoint > 0)
			{
				if (this->tabs[i]->IsButtonPressed("vitality+") && this->GetKeyTime())
				{
					this->player.GetAC()->vitality++;
					this->player.GetAC()->attributePoint--;
					this->player.GetAC()->UpdateStats(true);
				}
				else if (this->tabs[i]->IsButtonPressed("strength+") && this->GetKeyTime())
				{
					this->player.GetAC()->strength++;
					this->player.GetAC()->attributePoint--;
					this->player.GetAC()->UpdateStats(true);
				}
				else if (this->tabs[i]->IsButtonPressed("agility+") && this->GetKeyTime())
				{
					this->player.GetAC()->agility++;
					this->player.GetAC()->attributePoint--;
					this->player.GetAC()->UpdateStats(true);
				}
				else if (this->tabs[i]->IsButtonPressed("intelligence+") && this->GetKeyTime())
				{
					this->player.GetAC()->agility++;
					this->player.GetAC()->attributePoint--;
					this->player.GetAC()->UpdateStats(true);
				}
			}
			
		}
	}
}

Tab* PlayerTabs::GetCharTab()
{
	return this->tabs[0];
}



void PlayerTabs::Render(RenderTarget& target)
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->GetOpen())
		{
			this->tabs[i]->Render(target);
		}
	}
}
