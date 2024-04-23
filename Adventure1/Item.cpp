#include "stdafx.h"
#include "Item.h"

void Item::InitVal()
{
	
}

Item::Item(unsigned value)
{
	this->InitVal();
	this->value = value;
	this->type = ItemTypes::DEFAULT_ITEM;
}
Item::~Item()
{
}
