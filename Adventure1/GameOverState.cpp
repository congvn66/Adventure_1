#include "stdafx.h"
#include "GameOverState.h"
GameOverState::GameOverState(StateData* stateData)
	:State(stateData)
{
	this->InitVal();
	this->InitFont();
	this->InitKeybinds();
	this->InitButton();
}

void GameOverState::InitVal()
{
}



void GameOverState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
}

void GameOverState::InitFont()
{
	//load font
	if (font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF")) {
		cout << "Game Over: Font loaded!" << endl;
	}
	else {
		cout << "Game Over: Font failed to load!" << endl;
	}
}

void GameOverState::InitButton()
{
	//setting up buttons
	this->buttons["GAME_OVER"] = new gui::Button(850+45, 436, 120.f, 60.f,
		&this->font, "Game Over!", Color::Transparent, Color::Transparent, Color::Transparent, Color::Red, Color::Red, Color::Red,
		Color::Transparent, Color::Transparent, Color::Transparent, 0, 100);
	this->buttons["QUIT"] = new gui::Button(850+45, 436 + 300, 120.f, 60.f,
		&this->font, "Quit", Color::Transparent, Color::Transparent, Color::Transparent, Color::White, Color::White, Color::White,
		Color::Transparent, Color::Transparent, Color::Transparent,0,50);
}

GameOverState::~GameOverState()
{

	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void GameOverState::Update(const float& deltaTime)
{
	//it is w it is
	this->UpdateMousePos();

	//handle input by keyboard
	this->UpdateInput(deltaTime);

	//update states of buttons
	this->UpdateButton();
}

void GameOverState::Render(RenderTarget* target)
{
	//render menu
	if (target == nullptr) {
		target = this->window;
	}

	//render buttons
	this->RenderButtons(*target);
}

void GameOverState::UpdateInput(const float& deltaTime)
{
}

void GameOverState::UpdateButton()
{
	//this how to loop thru all elements in a map?
	//Update mouse
	for (auto& it : this->buttons) {
		it.second->Update(this->mousePosWindow);
	}
	//check for quit?
	if (this->buttons["QUIT"]->IsPressed()) {
		this->EndState();
	}
}

void GameOverState::RenderButtons(RenderTarget& target)
{
	//this how to loop thru all elements in a map?
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}