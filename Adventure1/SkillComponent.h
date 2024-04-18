#pragma once

enum SKILLS { HEALTH = 0, ATTACK , ACCURACY, ENDURANCE };

class SkillComponent
{
private:
	class Skill {
	private:
		int type;
		int level;
		int levelLim;
		int exp;
		int expNext;
	public:
		Skill(int type) {
			this->type = type;
			this->level = 1;
			this->levelLim = 99;
			this->exp = 0;
			this->expNext = 100;
		}
		~Skill() {

		}
		const int& GetType() const
		{
			return this->type;
		}
		const int& GetLevel() const
		{
			return this->level;
		}
		const int& GetExp() const
		{
			return this->exp;
		}
		const int& GetExpNext() const
		{
			return this->expNext;
		}

		void SetLevel(const int level)
		{
			this->level = level;
		}
		void SetLevelLim(const int levelLim)
		{
			this->levelLim = levelLim;
		}
		void SetExp(const int exp)
		{
			this->exp = exp;
		}
		void SetExpNext(const int expNext)
		{
			this->expNext = expNext;
		}

		void GainExp(const int exp)
		{
			this->exp += exp;
			this->UpdateLevel();
		}

		void LoseExp(const int exp)
		{
			this->exp -= exp;
			/*if (this->exp < 0)
			{
				this->exp = 0;
			}*/
		}

		void UpdateLevel(const bool up = true) {

			//Increase or decrease level if have a deficit or not
			if (up)
			{
				if (this->level < this->levelLim)
				{
					while (this->exp >= this->expNext)
					{
						if (this->level < this->levelLim)
						{
							this->level++;
							this->expNext = pow(this->level, 2) + this->level * 12;
						}

					}
				}
			}
			else
			{
				if (this->level > 0)
				{
					while (this->exp < 0)
					{
						if (this->level > 0)
						{
							this->level--;
							this->expNext = pow(this->level, 2) + this->level * 12;
						}

					}
				}
			}
		}
		void Update()
		{
		}
	};
	vector <Skill> skills;
public:
	SkillComponent();
	~SkillComponent();

	int GetSkill(const int skill);
	void GainExp(const int skill, int exp);
};

