#include "stdafx.h"
#include "Gui.h"
//-----------------------------BUTTONS---------------------------------------------------
gui::Button::Button(float x, float y, float width, float height, Font* font,
	string text, Color idleColor, Color hoverColor, Color activeColor,Color idleTextColor,
Color hoverTextColor,Color activeTextColor, Color outlineIdleColor,
Color outlineHoverColor, Color outlineActiveColor, short unsigned id)
{
	this->id = id;
	//basic settings
	this->buttonState = B_IDLE;
	this->shape.setSize(Vector2f(width, height));
	this->shape.setPosition(Vector2f(x, y));
	this->shape.setOutlineColor(outlineIdleColor);

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
	
	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;

	this->idleTextColor = idleTextColor;
	this->hoverTextColor = hoverTextColor;
	this->activeTextColor = activeTextColor;

	this->shape.setFillColor(idleColor);
}
gui::Button::~Button()
{
}
void gui::Button::Update(const Vector2f& mousePos)
{
	//idle
	this->buttonState = B_IDLE;

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
		this->text.setFillColor(this->idleTextColor);
		this->shape.setFillColor(this->idleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);	
		break;
	case B_ACTIVATED:
		this->shape.setFillColor(this->activeColor); 
		this->text.setFillColor(this->hoverTextColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;
	case B_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->activeTextColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;
	default:
		break;
	}
}
void gui::Button::Render(RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
const bool gui::Button:: IsPressed() const {
	if (this->buttonState == B_ACTIVATED) {
		return true;
	}
	return false;
}
const string gui::Button::getText() const
{
	return this->text.getString();
}
const short unsigned& gui::Button::GetId() const
{
	// TODO: insert return statement here
	return this->id;
}
void gui::Button::setText(const string text)
{
	this->text.setString(text);
}
void gui::Button::SetId(const short unsigned id)
{
	this->id = id;
}
//-----------------------------BUTTONS---------------------------------------------------

//------------------------DROP DOWN LIST-------------------------------------------------
gui::DropDownList::DropDownList(float x, float y,float width, float height,Font& font, 
	string list[], unsigned nrOfElements, unsigned default_index)
	:font(font), showList(false),keyTimeMax(1.f), keyTime(0.f)
{
	this->activeElement = new Button(x, y, width, height,
		&this->font, list[default_index], Color::Black, Color::White, Color::White,
		Color::White, Color::Black, Color::Black,Color(255,255,255,200), Color(255,255,255,255), Color(20,20,20,50));
	for (size_t i = 0; i < nrOfElements; i++) {
		this->list.push_back(new gui::Button(x, y+(i+1)*height, width, height,
			&this->font, list[i], Color::Black, Color::White, Color::White,
			Color::White, Color::Black, Color::Black, 
			Color(255, 255, 255, 0), Color(255, 255, 255,0), Color(20, 20, 20, 0),i));
	}
	
}
gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++) {
		delete this->list[i];
	}
}
const bool gui::DropDownList::GetKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}
void gui::DropDownList::UpdateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax) {
		this->keyTime += 10.f * dt;
	}
}
void gui::DropDownList::Update(const Vector2f& mousePos, const float& dt)
{
	this->UpdateKeyTime(dt);
	this->activeElement->Update(mousePos);

	//show & hide the list
	if (this->activeElement->IsPressed()&&this->GetKeyTime()) {
		if (this->showList) {
			this->showList = false;
		}
		else {
			this->showList = true;
		}
	}
	if (this->showList) {
		for (auto& i : this->list) {
			i->Update(mousePos);

			//update the chosen one
			if (i->IsPressed() && this->GetKeyTime()) {
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->SetId(i->GetId());
			}
		}
	}
	
}
void gui::DropDownList::Render(RenderTarget& target)
{
	this->activeElement->Render(target);
	if (this->showList) {
		for (auto& i : this->list) {
			i->Render(target);
		}
	}
}
//------------------------DROP DOWN LIST-------------------------------------------------

//-------------------------TEXTURE SELECTOR----------------------------------------------
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,const Texture* textureSheet)
{
	this->bound.setSize(Vector2f(width, height));
	this->bound.setPosition(x, y);
	this->bound.setFillColor(Color(50, 50, 50, 100));
	this->bound.setOutlineThickness(2.f);
	this->bound.setOutlineColor(Color(255, 255, 255, 200));
	this->sheet.setTexture(*textureSheet);
	this->sheet.setPosition(x, y);

	if (this->sheet.getGlobalBounds().width > this->bound.getGlobalBounds().width) {
		this->sheet.setTextureRect(IntRect(0, 0, this->bound.getGlobalBounds().width, 
			this->bound.getGlobalBounds().height));
	}

	if (this->sheet.getGlobalBounds().height > this->bound.getGlobalBounds().height) {
		this->sheet.setTextureRect(IntRect(0, 0, this->bound.getGlobalBounds().height,
			this->bound.getGlobalBounds().width));
	}
}

gui::TextureSelector::~TextureSelector()
{
}
void gui::TextureSelector::Update()
{

}
void gui::TextureSelector::Render(RenderTarget& target)
{
	target.draw(this->bound);
	target.draw(this->sheet);
}
//-------------------------TEXTURE SELECTOR----------------------------------------------