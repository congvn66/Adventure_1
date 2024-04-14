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
	unsigned vitality; //max health
	unsigned strength; //crush the tomato
	unsigned dexterity;//dodge the tomato
	unsigned intelligence;//knowing the tomato?
	unsigned constitution; //eat the rotten tomato
	unsigned agility; // run

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
	void CalulateExpNext();
	void UpdateStats();
	void LevelUp();
	void Update();
};

