#include "Button.h"

Button::Button(float x, float y, float width, float height, Font* font,
	string text, Color idleColor, Color hoverColor, Color activeColor)
{
	//basic settings
	this->buttonState = B_IDLE;
	this->shape.setSize(Vector2f(width, height));
	this->shape.setPosition(Vector2f(x, y));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(Color::Black);
	this->text.setCharacterSize(36);
	this->text.setPosition(this->shape.getPosition().x +this->shape.getGlobalBounds().width/2.f - this->text.getGlobalBounds().width / 2.f
		,this->shape.getPosition().y + this->shape.getGlobalBounds().height/ 2.f - this->text.getGlobalBounds().height / 2.f);


	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(idleColor);
}

Button::~Button()
{
}

void Button::Update(const Vector2f mousePos)
{
	//idle
	this->buttonState = B_IDLE;
	this->text.setFillColor(Color::Black);

	//hover
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->buttonState = B_HOVER;

		//press
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = B_ACTIVATED;
		}
	}

	//update color for each state
	switch (this->buttonState)
	{
	case B_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;
	case B_ACTIVATED:
		this->shape.setFillColor(this->activeColor); 
		this->text.setFillColor(Color::White);
		break;
	case B_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(Color::White);
		break;
	default:
		break;
	}
}

void Button::Render(RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

const bool Button:: IsPressed() const {
	if (this->buttonState == B_ACTIVATED) {
		return true;
	}
	return false;
}
