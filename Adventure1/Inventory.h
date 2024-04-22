#pragma once

#include "Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned numOfItems;
	unsigned capacity;

	void Init();
	void Clear();
	void Nullify(const unsigned from=0);
public:
	Inventory(unsigned capacity);
	~Inventory();

	const unsigned& size() const;
	const unsigned& MaxSize() const;
	void clear();
	const bool Empty() const;
	const bool Add(Item* item);
	const bool Remove(const unsigned index);

	const bool SaveToFile(string fileName);
	const bool LoadFromFile(string fileName);
};

