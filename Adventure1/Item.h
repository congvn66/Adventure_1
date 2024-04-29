#pragma once

//just general item class for every item

enum ItemTypes
{
	DEFAULT_ITEM = 0,
	RANGED,
	MELEE
};
enum ItemLevels
{
	COMMON = 0,
	RARE,
	EPIC,
	LEGENDARY,
	MYTHIC
};

class Item
{
private:
	void InitVal();
protected:
	unsigned value;
	unsigned level;
	short unsigned type;
public:
	Item(unsigned level, unsigned value);
	~Item();

	virtual Item* clone() = 0;
};

