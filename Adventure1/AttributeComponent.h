#pragma once

//things to describe stat of enities

class AttributeComponent
{
public:
	//leveling
	int level;
	int exp;
	int expNext;
	int attributePoint;

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
	AttributeComponent(int level);
	~AttributeComponent();

	//func
	void LoseHP(const int hp);
	void LoseEXP(const int exp);
	void GainHP(const int hp);
	void GainExp(const int exp);
	void UpdateStats(const bool reset);
	void Update();
	void UpdateLevel();
};

