#include "stdafx.h"
#include "Item.h"

void Item::InitVal()
{
	
}

Item::Item(unsigned level, unsigned value)
{
	this->InitVal();
	this->level = level;
	this->value = value;
	this->type = ItemTypes::DEFAULT_ITEM;
}
Item::~Item()
{
}
