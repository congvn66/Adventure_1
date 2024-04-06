#include "stdafx.h"
#include "GameState.h"

//--------------------------------INITIALIZE------------------------------------------
void GameState::InitKeybinds()
{
	//map added supported keys into funtion name (in fact just map with an int)
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");

}
void GameState::InitFont()
{
	//load font
	if (this->font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF")) {
		cout << "Game State: Font loaded!" << endl;
	}
	else {
		cout << "Game State: Font failed to load!" << endl;
	}
}
void GameState::InitPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->AddButton("QUIT", 800.f, "Quit");
}
void GameState::InitTexture()
{
	Texture temp;
	if (temp.loadFromFile("Assets/Player/Texture/Player_sheet.png")) {
		cout << "GameState: Player sheet loaded!" << endl;
	}
	this->textures["PLAYER_SHEET"] = temp;
}
void GameState::InitPlayer()
{
	this->player = new Player(100, 100, this->textures["PLAYER_SHEET"]);
}
//--------------------------------INITIALIZE------------------------------------------
// 
//---------------------------------CON & DE-------------------------------------------
GameState::GameState(RenderWindow* window, std::map <string, int>* supportedKeys, stack <State*>* states)
	:State(window, supportedKeys, states)
{
	this->InitKeybinds();
	this->InitFont();
	this->InitTexture();
	this->InitPauseMenu();
	this->InitPlayer();
}
GameState::~GameState()
{
	delete this->player;
	delete this->pauseMenu;
}
//---------------------------------CON & DE-------------------------------------------
// 
//------------------------------------FUNCTION----------------------------------------
void GameState::UpdateInput(const float& dt)
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE"))) && this->GetKeyTime()) {
		//pause if it not paused already
		if (this->pause == false) {
			this->PauseState();
		}
		else {
			this->UnpauseState();
		}
	}
}
void GameState::Update(const float& deltaTime)
{
	//update in main game
	this->UpdateMousePos();
	this->UpdatekeyTime(deltaTime);
	this->UpdateInput(deltaTime);
	if (this->pause == false) { // unpause
		this->UpdatePlayerInput(deltaTime);
		this->player->Update(deltaTime);
	}
	else { //when in pause menu
		this->pauseMenu->Update(this->mousePosView);
		this->UpdatePauseMenuButton();
	}
}
void GameState::UpdatePauseMenuButton()
{
	//in pause menu
	if (this->pauseMenu->IsButtonPressed("QUIT")) {
		this->EndState();
	}
}
void GameState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	this->map.Render(*target);
	this->player->Render(*target);

	if (this->pause == true) {
		this->pauseMenu->Render(*target);
	}
	
}
void GameState::UpdatePlayerInput(const float& deltaTime)
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
}
//------------------------------------FUNCTION----------------------------------------