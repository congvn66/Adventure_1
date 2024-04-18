#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(SKILLS::HEALTH));
	this->skills.push_back(Skill(SKILLS::ATTACK));
	this->skills.push_back(Skill(SKILLS::ACCURACY));
	this->skills.push_back(Skill(SKILLS::ENDURANCE));
}

SkillComponent::~SkillComponent()
{
}

int SkillComponent::GetSkill(const int skill)
{
	if (skill >= 0 && skill < this->skills.size() && !this->skills.empty()) //valid index
	{
		return this->skills[skill].GetLevel(); // return level of the skill
	}
	return -1;
}

void SkillComponent::GainExp(const int skill, int exp)
{
	if (skill >= 0 && skill < this->skills.size() && !this->skills.empty()) //valid index
	{
		this->skills[skill].GainExp(exp); // return level of the skill
	}
}
