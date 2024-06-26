#pragma once

using namespace sf;
using namespace std;

enum ButtonStates{B_IDLE =0, B_HOVER, B_ACTIVATED};
namespace gui {
	class Button
	{
	private:
		//state
		short unsigned buttonState;
		bool pressed;
		bool hover;
		short unsigned id;

		//elements
		RectangleShape shape;
		Font* font;
		Text text;

		Color idleColor;
		Color hoverColor;
		Color activeColor;

		Color outlineIdleColor;
		Color outlineHoverColor;
		Color outlineActiveColor;

		Color idleTextColor;
		Color hoverTextColor;
		Color activeTextColor;
	public:
		//constructor, deconstructor
		Button(float x, float y, float width, float height, Font* font,
			string text, Color idleColor, Color hoverColor, Color activeColor, Color idleTextColor,
			Color hoverTextColor, Color activeTextColor, Color outlineIdleColor=Color::Transparent, 
			Color outlineHoverColor = Color::Transparent,
			Color outlineActiveColor = Color::Transparent,short unsigned id=0,int characterSize=36);
		~Button();

		//look in cpp file
		const bool IsPressed() const;
		const string getText() const;
		const short unsigned& GetId() const;

		void setText(const string text);
		void SetId(const short unsigned id);

		void Update(const Vector2i& mousePosWindow);
		void Render(RenderTarget& target);
	};
	class DropDownList {
	private:
		float keyTime;
		float keyTimeMax;
		Font& font;
		gui::Button* activeElement;
		vector <gui::Button*> list;
		bool showList;
	public:
		DropDownList(float x, float y, float width, float height,Font& font, string list[],unsigned nrOfElements, unsigned default_index=0);
		~DropDownList();

		const bool GetKeyTime();
		void UpdateKeyTime(const float& dt);
		void Update(const Vector2i& mousePosWindow, const float& dt);
		void Render(RenderTarget& target);
	};
	class TextureSelector {
	private:
		float keyTime;
		const float keyTimeMax;
		RectangleShape bound;
		Sprite sheet;
		RectangleShape selector;
		Vector2u mousePosGrid;
		IntRect texRect;
		float gridSize;
		bool active;
		bool hidden;
		Button* hide;
	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, 
			const Texture* textureSheet,Font& font,string text);
		~TextureSelector();

		const bool GetKeyTime();
		void UpdateKeyTime(const float& dt);
		const bool& GetActive() const;
		const IntRect& GetTexRect() const;
		void Update(Vector2i& mousePosWindow, const float& dt);
		void Render(RenderTarget& target);

	};
}
