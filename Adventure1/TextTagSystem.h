#pragma once

enum TagType { DEFAULT_TAG = 0, NEGATIVE_TAG, POSITIVE_TAG, EXPERIENCE_TAG, EVIRONMENTAL_TAG};

class TextTagSystem
{
private:
	class TextTag
	{
	private:
		Text text;
		float dirY;
		float dirX;
		float lifeTime;
		float speed;
		float acceleration;
		Vector2f velocity;
		bool reverse;
	public:
		TextTag(Font& font, string text, float posX, float posY, float dirX, float dirY,
			Color color, unsigned charSize, float lifeTime,bool reverse, float speed, float acceleration) {
			this->text.setFont(font);
			this->text.setPosition(posX, posY);
			this->dirX = dirX;
			this->dirY = dirY;
			this->lifeTime = lifeTime;
			this->speed = speed;
			this->acceleration = acceleration;
			this->text.setFillColor(color);
			this->text.setCharacterSize(charSize);
			this->text.setString(text);
			this->reverse = reverse;
			if (this->reverse)
			{
				this->velocity.x = this->dirX * this->speed;
				this->velocity.y = this->dirY * this->speed;
			}
		}
		TextTag(TextTag* tag, float posX, float posY,string text) {
			this->text = tag->text;
			this->text.setString(text);
			this->text.setPosition(posX, posY);
			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
			this->acceleration = tag->acceleration;
			this->reverse = tag->reverse;
			this->velocity = tag->velocity;
			
		}
		~TextTag()
		{

		}
		const bool CanBeDeleted() const
		{
			return this->lifeTime <= 0.f;
		}
		void Update(const float& dt)
		{
			if (!this->CanBeDeleted())
			{
				//lifeTime update
				this->lifeTime -= 100.f * dt;

				//accelerate
				if (this->acceleration > 0.f)
				{
					if (this->reverse)
					{
						this->velocity.x -= this->dirX * this->acceleration * dt;
						this->velocity.y -= this->dirY * this->acceleration * dt;

						//speed limit
						if (abs(this->velocity.x) < 0.f)
						{
							this->velocity.x = 0.f;
						}

						if (abs(this->velocity.y) < 0.f)
						{
							this->velocity.y = 0.f;
						}

						this->text.move(this->velocity * dt);
					}
					else
					{
						this->velocity.x += this->dirX * this->acceleration * dt;
						this->velocity.y += this->dirY * this->acceleration * dt;

						//speed limit
						if (abs(this->velocity.x) > this->speed)
						{
							this->velocity.x = this->dirX * this->speed;
						}

						if (abs(this->velocity.y) > this->speed)
						{
							this->velocity.y = this->dirY * this->speed;
						}

						this->text.move(this->velocity * dt);
					}
				}
				else
				{

				}

				//move
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);

			}

		}
		void Render(RenderTarget& target)
		{
			target.draw(this->text);
		}

	};
	Font font;
	vector <TextTag*> tags;
	map <unsigned, TextTag*> tagTemplates; // generate templates for tag types
	void InitVal();
	void InitTagTemplates();
	void InitFont(string fontFile);
public:
	TextTagSystem(string fontFile);
	~TextTagSystem();
	void AddTextTag(unsigned tagType,const float posX,const float posY,const string text, const string prefix = "", const string postfix = "");
	void AddTextTag(unsigned tagType, const float posX, const float posY, const int val, const string prefix = "", const string postfix = "");
	void AddTextTag(unsigned tagType, const float posX, const float posY, const float val, const string prefix = "", const string postfix = "");

	void Update(const float& dt);
	void Render(RenderTarget& target);
};

