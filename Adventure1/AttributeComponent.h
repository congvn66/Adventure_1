#pragma once

//things to describe stat of enities

class AttributeComponent
{
public:
	//leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoint;

	//attributes
	int vitality; //max health
	int strength; //crush the tomato
	int dexterity;//dodge the tomato
	int intelligence;//knowing the tomato?
	int agility; // run

	//stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int dodge;
	int luck;

	//con & de
	AttributeComponent(unsigned level);
	~AttributeComponent();

	//func
	void GainExp(const unsigned exp);
	void UpdateStats(const bool reset);
	void Update();
	void UpdateLevel();
};

