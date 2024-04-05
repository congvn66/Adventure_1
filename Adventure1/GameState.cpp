#include "GameState.h"

void GameState::InitKeybinds()
{
	//map added supported keys into funtion name (in fact just map with an int)
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");

}

void GameState::InitTexture()
{
	Texture temp;
	if (temp.loadFromFile("Assets/Player/Texture/test.png")) {
		cout << "Player idle loaded!" << endl;
	}
	this->textures["PLAYER_IDLE"] = temp;
}

void GameState::InitPlayer()
{
	this->player = new Player(100, 100, this->textures["PLAYER_IDLE"]);
}

GameState::GameState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states)
	:State(window,supportedKeys, states)
{
	this->InitKeybinds();
	this->InitTexture();
	this->InitPlayer();
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::Update(const float& deltaTime)
{
	this->UpdateMousePos();
	this->UpdateInput(deltaTime);
	this->player->Update(deltaTime);

}

void GameState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	this->player->Render(target);
	
}

void GameState::UpdateInput(const float& deltaTime)
{
	//player update
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->player->Move(deltaTime, -2.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->player->Move(deltaTime, 2.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->player->Move(deltaTime, 0.0f, -2.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->player->Move(deltaTime, 0.0f, 2.0f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->EndState();
	}
}
