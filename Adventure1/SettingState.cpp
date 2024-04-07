#include "stdafx.h"
#include "SettingState.h"

SettingState::SettingState(StateData* stateData)
	:State(stateData)
{
	this->InitVal();
	this->InitFont();
	this->InitKeybinds();
	this->InitGui();
	this->InitBackground();

}

SettingState::~SettingState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = this->dropdownlist.begin();
	for (it2 = this->dropdownlist.begin(); it2 != this->dropdownlist.end(); ++it2)
	{
		delete it2->second;
	}
}

void SettingState::InitVal()
{
}

void SettingState::InitBackground()
{
	this->background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
	if (this->texture.loadFromFile("Assets/Image/Background/mainmenubackground.jpg")) {
		cout << "SettingState: background loaded!" << endl;
		this->background.setTexture(&this->texture);
	}
	else {
		cout << "SettingState: background failed to load!";
	}
}

void SettingState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
}

void SettingState::InitFont()
{
	//load font
	if (font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF")) {
		cout << "Main menu: Font loaded!" << endl;
	}
	else {
		cout << "Main menu: Font failed to load!" << endl;
	}
}

void SettingState::InitGui()
{
	//setting up GUI
	this->buttons["BACK"] = new gui::Button(1700, 880, 120.f, 30.f,
		&this->font, "Back", Color::Transparent, Color::Transparent, Color::Transparent, 
		Color::Black, Color::White, Color::White);
	this->buttons["YESSIR"] = new gui::Button(1500, 880, 120.f, 30.f,
		&this->font, "YESSIR", Color::Transparent, Color::Transparent, Color::Transparent,
		Color::Black, Color::White, Color::White);
	string li[3] = { "nope","yep","yope"};
	this->dropdownlist["TEST"] = new gui::DropDownList(800, 400, 120, 60, font, li, 3);
}

void SettingState::Update(const float& deltaTime)
{
	//it is w it is
	this->UpdateMousePos();

	//handle input by keyboard
	this->UpdateInput(deltaTime);

	//update states of buttons
	this->UpdateGui(deltaTime);

	
}

void SettingState::Render(RenderTarget* target)
{
	//render menu
	if (target == nullptr) {
		target = this->window;
	}
	target->draw(this->background);

	//render buttons
	this->RenderGui(*target);

}

void SettingState::UpdateInput(const float& deltaTime)
{
}

void SettingState::UpdateGui(const float& deltaTime)
{
	//this how to loop thru all elements in a map?
	//Update mouse
	for (auto& it : this->buttons) {
		it.second->Update(this->mousePosView);
	}
	
	//----------------BUTTONS-----------------
	// quit
	if (this->buttons["BACK"]->IsPressed()) {
		this->EndState();
	}
	//apply
	if (this->buttons["YESSIR"]->IsPressed()) {
		this->EndState();
	}
	//----------------BUTTONS-----------------

	//-------------------DROP DOWN-------------
	for (auto& it : this->dropdownlist) {
		it.second->Update(this->mousePosView, deltaTime);
	}
	//-------------------DROP DOWN-------------
}

void SettingState::RenderGui(RenderTarget& target)
{
	//this how to loop thru all elements in a map?
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}

	for (auto& it2 : this->dropdownlist) {
		it2.second->Render(target);
	}
}
