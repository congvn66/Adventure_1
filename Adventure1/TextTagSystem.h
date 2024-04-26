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
	public:
		TextTag(Font& font, string text, float posX, float posY, float dirX, float dirY,
			Color color, unsigned charSize, float lifeTime, float speed) {
			this->text.setFont(font);
			this->text.setPosition(posX, posY);
			this->dirX = dirX;
			this->dirY = dirY;
			this->lifeTime = lifeTime;
			this->speed = speed;
			this->text.setFillColor(color);
			this->text.setCharacterSize(charSize);
			this->text.setString(text);
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

				//move
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);

			}

		}
		void Render(RenderTarget* target)
		{
			target->draw(this->text);
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
	void AddTextTag(unsigned tagType);
	void RemoveTextTag();
	void Update(const float& dt);
	void Render(RenderTarget* target);
};

