#include "GameState.h"

void GameState::InitKeybinds()
{
	//map added supported keys into funtion name (in fact just map with an int)
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("S");

}

GameState::GameState(RenderWindow* window, map <string, int>* supportedKeys)
	:State(window,supportedKeys)
{
	this->InitKeybinds();
}

GameState::~GameState()
{
}

void GameState::EndState()
{
	cout << "end.";
}

void GameState::Update(const float& deltaTime)
{
	this->UpdateInput(deltaTime);

}

void GameState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	this->player.Render(target);
	
}

void GameState::UpdateInput(const float& deltaTime)
{
	this->CheckQuit();

	//player update
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->player.Move(deltaTime, -2.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->player.Move(deltaTime, 2.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->player.Move(deltaTime, 0.0f, -2.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->player.Move(deltaTime, 0.0f, 2.0f);
	}
}
