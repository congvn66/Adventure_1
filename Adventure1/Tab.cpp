#include "stdafx.h"
#include "Tab.h"

Tab::Tab(Font& font, Player& player, bool hidden)
	:font(font), player(player), hidden(hidden)
{
}

Tab::~Tab()
{
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
