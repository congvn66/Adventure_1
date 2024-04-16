#include "stdafx.h"
#include "GameState.h"

//--------------------------------INITIALIZE------------------------------------------
void GameState::InitDeferredRender()
{
	this->renderTexture.create(static_cast<unsigned>(1920), static_cast<unsigned>(1080));
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(IntRect(0, 0,1920,1080));
}
void GameState::InitView()
{
	this->view.setSize(Vector2f(1920.f, 1080.f));
	this->view.setCenter(Vector2f(1920.f / 2.f, 1080.f / 2.f));
}
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
void GameState::InitShader()
{
	if (!this->coreShader.loadFromFile("vertex_shader.vert", "fragmentshader.frag"))
	{
		cout << "GameState: failed to load shader!" << endl;
	}
	else
	{
		cout << "GameState: shader loaded!" << endl;
	}
}
void GameState::InitPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player);
}
void GameState::InitTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 1000, 1000, "Assets/Map/newtilesheet.png");
	this->tileMap->LoadFromFile("text.map");
}
void GameState::InitTexture()
{
	Texture temp;
	if (temp.loadFromFile("Assets/Player/Texture/Player_sheet2.png")) {
		cout << "GameState: Player sheet loaded!" << endl;
	}
	this->textures["PLAYER_SHEET"] = temp;
}
void GameState::InitPlayer()
{
	this->player = new Player(300,200, this->textures["PLAYER_SHEET"]);
}
//--------------------------------INITIALIZE------------------------------------------
// 
//---------------------------------CON & DE-------------------------------------------
GameState::GameState(StateData* stateData)
	:State(stateData)
{
	this->InitDeferredRender();
	this->InitView();
	this->InitKeybinds();
	this->InitFont();
	this->InitTexture();
	this->InitShader();
	this->InitPauseMenu();

	this->InitPlayer();
	this->InitPlayerGUI();
	this->InitTileMap();
}
GameState::~GameState()
{
	delete this->playerGUI;
	delete this->player;
	delete this->pauseMenu;
	delete this->tileMap;
}
//---------------------------------CON & DE-------------------------------------------
// 
//------------------------------------FUNCTION----------------------------------------
void GameState::UpdateView(const float& deltaTime)
{
	this->view.setCenter(floor(this->player->GetPos().x + (static_cast<float>(this->mousePosWindow.x)-static_cast<float>(1920/2)) / 5.f),
		floor(this->player->GetPos().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(1080 / 2)) / 5.f));
}
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
void GameState::UpdatePlayerGUI(const float& deltaTime)
{
	this->playerGUI->Update(deltaTime);
}
void GameState::Update(const float& deltaTime)
{
	//update in main game
	this->UpdateMousePos(&this->view);
	this->UpdatekeyTime(deltaTime);
	this->UpdateInput(deltaTime);
	if (!this->pause) { // unpause
		this->UpdateView(deltaTime);
		this->UpdatePlayerInput(deltaTime);
		this->UpdateTileMap(deltaTime);
		this->player->Update(deltaTime);
		this->UpdatePlayerGUI(deltaTime);
	}
	else { //when in pause menu
		this->pauseMenu->Update(this->mousePosWindow);
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
void GameState::UpdateTileMap(const float& dt)
{
	this->tileMap->Update();
	this->tileMap->UpdateCollision(this->player,dt);
}
void GameState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	this->renderTexture.clear();
	//map
	this->renderTexture.setView(this->view);
	this->tileMap->Render(this->renderTexture,this->player->getGridPos(static_cast<int>(this->stateData->gridSize)),false);

	//player
	this->player->Render(this->renderTexture,nullptr,false);

	//render upper layers of the map
	this->tileMap->RenderDefered(this->renderTexture);

	//player Gui
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->Render(this->renderTexture);

	//pmenu
	if (this->pause) {
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pauseMenu->Render(this->renderTexture);
	}
	
	//final
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
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