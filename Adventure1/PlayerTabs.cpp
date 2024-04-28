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

void PlayerTabs::Update()
{
	for (size_t i = 0; i < this->tabs.size(); i++)
	{
		if (this->tabs[i]->GetOpen())
		{
			this->tabs[i]->Update();
		}
	}
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
