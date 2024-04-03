#include "MainMenuState.h"

MainMenuState::MainMenuState(RenderWindow* window, map <string, int>* supportedKeys)
	:State(window,supportedKeys)
{
	this->InitKeybinds();
	this->background.setSize(Vector2f(window->getSize().x,window->getSize().y));
	this->background.setFillColor(Color::Green);
}

void MainMenuState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("S");
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::EndState()
{
}

void MainMenuState::Update(const float& deltaTime)
{
	this->UpdateInput(deltaTime);
}

void MainMenuState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	target->draw(this->background);
}

void MainMenuState::UpdateInput(const float& deltaTime)
{
	this->CheckQuit();
}
