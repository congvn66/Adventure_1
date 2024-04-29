#include "stdafx.h"
#include "Inventory.h"

void Inventory::Init()
{
	this->numOfItems = 0;
	this->itemArray = new Item * [this->capacity];
	this->Nullify();
}

void Inventory::Clear()
{
	for (size_t i = 0; i < this->numOfItems; i++)
	{
		delete this->itemArray[i];
	}

	delete[] this->itemArray;
}


void Inventory::Nullify(const unsigned from)
{
	for (size_t i = from; i < this->capacity; i++)
	{
		this->itemArray[i] = nullptr;
	}
}

Inventory::Inventory(unsigned capacity)
{
	this->capacity = capacity;

	this->Init();
}

Inventory::~Inventory()
{
	this->Clear();
}

const unsigned& Inventory::size() const
{
	return this->numOfItems;
}

const unsigned& Inventory::MaxSize() const
{
	return this->capacity;
}

void Inventory::clear()
{
	for (size_t i = 0; i < this->numOfItems; i++)
	{
		delete this->itemArray[i];
	}
	this->numOfItems = 0;
	this->Nullify();
}

const bool Inventory::Empty() const
{
	return this->numOfItems==0;
}

const bool Inventory::Add(Item* item)
{
	if (this->numOfItems < this->capacity)
	{
		this->itemArray[this->numOfItems++] = item->clone();;
		return true;
	}
	return false;
}

const bool Inventory::Remove(const unsigned index)
{
	if (this->numOfItems > 0)
	{
		if (index < capacity && index >=0)
		{
			delete this->itemArray[index];
			this->itemArray[index] = nullptr;
			this->numOfItems--;
			return true;
		}
	}
	return false;
}

const bool Inventory::SaveToFile(string fileName)
{
	return false;
}

const bool Inventory::LoadFromFile(string fileName)
{
	return false;
}
