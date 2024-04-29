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
	this->view.setSize(Vector2f(1920.f/1.5, 1080.f/1.5));
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
	this->keybinds["OPEN_CHAR_TAB"] = this->supportedKeys->at("TAB");
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
	this->pauseMenu->AddButton("RESIGN", 800.f, "Resign");
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
	this->playerGUI->GetPlayerTabs()->GetCharTab()->AddButton("vitality+", 600.f, "VITALITY+");
	this->playerGUI->GetPlayerTabs()->GetCharTab()->AddButton("strength+", 660.f, "STRENGTH+");
	this->playerGUI->GetPlayerTabs()->GetCharTab()->AddButton("agility+", 720.f, "AGILITY+");
	this->playerGUI->GetPlayerTabs()->GetCharTab()->AddButton("intelligence+", 780.f, "INTELLIGENCE+");
}
void GameState::InitEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}
void GameState::InitTileMap()
{
	this->tileMap = new TileMap("text.map");
}
void GameState::InitTextTag()
{
	this->tts = new TextTagSystem("Assets/Font/joystix monospace.otf");
}
void GameState::InitTexture()
{
	Texture temp;
	if (temp.loadFromFile("Assets/Player/Texture/Player_sheet2.png")) {
		cout << "GameState: Player sheet loaded!" << endl;
	}
	this->textures["PLAYER_SHEET"] = temp;

	//enemies
	if (this->textures["ORC_SHEET"].loadFromFile("Assets/Enemy/Texture/orc.png"))
	{
		cout << "GameState: Orc sheet loaded!" << endl;
	}
	if (this->textures["SKELLY_SHEET"].loadFromFile("Assets/Enemy/Texture/skelly.png"))
	{
		cout << "GameState: Skelly sheet loaded!" << endl;
	}
	if (this->textures["WRAITH_SHEET"].loadFromFile("Assets/Enemy/Texture/wraith.png"))
	{
		cout << "GameState: Wraith sheet loaded!" << endl;
	}
	if (this->textures["ZOMBIE_SHEET"].loadFromFile("Assets/Enemy/Texture/zombie.png"))
	{
		cout << "GameState: Zombie sheet loaded!" << endl;
	}
	if (this->textures["BOSS_SHEET"].loadFromFile("Assets/Enemy/Texture/boss.png"))
	{
		cout << "GameState: Boss sheet loaded!" << endl;
	}
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

	this->InitTextTag();
	this->InitPlayer();
	this->InitPlayerGUI();
	this->InitEnemySystem();
	this->InitTileMap();

	//this->test = new Player(200, 300, this->textures["PLAYER_SHEET"]);
}
GameState::~GameState()
{
	delete this->playerGUI;
	delete this->player;
	delete this->pauseMenu;
	delete this->tileMap;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
	delete this->tts;

	delete this->enemySystem;
}
//---------------------------------CON & DE-------------------------------------------

//------------------------------------FUNCTION----------------------------------------
void GameState::Update(const float& deltaTime)
{
	//update in main game
	this->UpdateMousePos(&this->view);
	this->UpdatekeyTime(deltaTime);
	this->UpdateInput(deltaTime);
	if (!this->pause) { // unpause
		this->UpdateView(deltaTime);

		//player
		this->UpdatePlayerInput(deltaTime);
		this->UpdateTileMap(deltaTime);
		this->UpdatePlayer(deltaTime);
		this->UpdatePlayerGUI(deltaTime);
		
		//enemies
		this->UpdateCombatAndEnemies(deltaTime);
		
		//text tag
		this->tts->Update(deltaTime);

		if (this->player->GetAC()->hp == 0)
		{
			this->EndState();
		}
		
	}
	else { //when in pause menu
		this->pauseMenu->Update(this->mousePosWindow);
		this->UpdatePauseMenuButton();
	}
}
void GameState::UpdatePlayer(const float& dt)
{

	this->player->Update(dt, this->mousePosView, this->view);

	//gui
	//this->UpdatePlayerGUI(dt);
}
void GameState::UpdateCombatAndEnemies(const float& dt)
{
	if (Mouse::isButtonPressed(Mouse::Left)&& this->player->GetWeapon()->GetAtkTimer())
	{
		this->player->SetInitAttack(true);
	}
	int index = 0;
	for (auto* enemy : this->activeEnemies)
	{
		enemy->Update(dt, this->mousePosView, this->view);

		this->tileMap->UpdateWorldBoundCollision(enemy, dt);
		this->tileMap->UpdateTileCollision(enemy, dt);
		
		this->UpdateCombat(enemy,index, dt);

		//delete enemies if die
		if (enemy->IsDead())
		{
			this->player->GainEXP(enemy->GetGainExp());
			this->tts->AddTextTag(TagType::EXPERIENCE_TAG, this->player->GetCenterPos().x-40.f, 
				this->player->GetCenterPos().y-30.f, static_cast<int>(enemy->GetGainExp()),"+","exp");

			//cout << "kill" << endl;

			this->enemySystem->removeEnemy(index);
			continue;
		}
		else if (enemy->GetDespawnTimerDone()) // despawn enemies if outside the view
		{
			this->enemySystem->removeEnemy(index);
			continue;
		}

		++index;
	}
	this->player->SetInitAttack(false);
}
void GameState::UpdateView(const float& deltaTime)
{
	
	this->view.setCenter(floor(this->player->GetPos().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(1920 / 2)) / 10.f),
		floor(this->player->GetPos().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(1080 / 2)) / 10.f));

	//make sure the camera wont go out the screen
	if (this->view.getSize().x <= this->tileMap->GetMaxSizeF().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f) //left most part of view pass the screen
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x - this->view.getSize().x / 2.f > this->tileMap->GetMaxSizeF().x)//right most part of view pass the screen
		{
			this->view.setCenter(this->tileMap->GetMaxSizeF().x - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}

	if (this->view.getSize().y <= this->tileMap->GetMaxSizeF().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)//up most part of view pass the screen
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y - this->view.getSize().y / 2.f > this->tileMap->GetMaxSizeF().y)//down most part of view pass the screen
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->GetMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}
	

	this->viewGridPos.x = static_cast<int> (this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPos.y = static_cast<int> (this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
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
	this->playerGUI->Update(deltaTime, this->mousePosWindow);

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("OPEN_CHAR_TAB"))) && this->GetKeyTime())
	{
		this->playerGUI->ToggleCharacterTab();
	}
}
void GameState::UpdatePauseMenuButton()
{
	//in pause menu
	if (this->pauseMenu->IsButtonPressed("RESIGN")) {
		this->EndState();
	}
}

void GameState::UpdateTileMap(const float& dt)
{
	this->tileMap->UpdateWorldBoundCollision(this->player, dt);
	this->tileMap->UpdateTileCollision(this->player, dt);
	this->tileMap->UpdateTiles(this->player,dt, *this->enemySystem);
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
void GameState::UpdateCombat(Enemy* enemy, const int index, const float dt)
{
	if (this->player->GetInitAttack() && enemy->GetGlobalBounds().contains(this->mousePosView) &&
		enemy->GetDistance(*this->player) < this->player->GetWeapon()->GetRange()&&
		enemy->GetDmgTimerDone())
	{
		//our damage
		enemy->LoseHP(this->player->GetDmg());
		enemy->ResetDmgTimer();
		this->tts->AddTextTag(TagType::DEFAULT_TAG, enemy->GetCenterPos().x-50.f, enemy->GetCenterPos().y, static_cast<int>(this->player->GetWeapon()->GetDamage()),"","");
	}
	//enemies' damage
	if (enemy->GetGlobalBounds().intersects(this->player->GetGlobalBounds())&&this->player->GetDmgTimer())
	{
		int dmg = enemy->GetDmg();
		this->player->LoseHP(dmg);
		this->tts->AddTextTag(TagType::NEGATIVE_TAG, player->GetPos().x - 30.f, player->GetPos().y, dmg, "-", "HP");	
	}
}
void GameState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	this->renderTexture.clear();
	//map
	this->renderTexture.setView(this->view);
	this->tileMap->Render(this->renderTexture,this->viewGridPos,false);

	//player
	this->player->Render(this->renderTexture,nullptr,true);

	//enemies
	for (auto* enemy : this->activeEnemies)
	{
		enemy->Render(this->renderTexture, nullptr, true);
	}

	//render upper layers of the map
	this->tileMap->RenderDefered(this->renderTexture);
	this->tts->Render(this->renderTexture);

	//player Gui
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->Render(this->renderTexture);

	//this->test->Render(this->renderTexture, nullptr, true);

	//pmenu
	if (this->pause && this->player->GetAC()->hp!=0) {
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pauseMenu->Render(this->renderTexture);
	}
	
	//final
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
//------------------------------------FUNCTION----------------------------------------