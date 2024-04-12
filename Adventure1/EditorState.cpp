#include "stdafx.h"
#include "EditorState.h"
//---------------------------------CON & DE-------------------------------------------
EditorState::EditorState(StateData* stateData)
	:State(stateData)
{
	this->InitVal();
	this->InitView();
	this->InitBackground();
	this->InitFont();
	this->InitText();
	this->InitKeybinds();
	this->InitPauseMenu();
	this->InitTileMap();
	this->InitButton();
	this->InitGui();
}
EditorState::~EditorState()
{
	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	//delete pmenu
	delete this->pauseMenu;
	//delete texture selector
	delete this->texSelector;
}
//---------------------------------CON & DE-------------------------------------------

//--------------------------------INITIALIZE------------------------------------------
void EditorState::InitView()
{
	this->view.setSize(Vector2f(1920, 1080));
	this->view.setCenter(1920 / 2.f, 1080 / 2.f);
}
void EditorState::InitText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(20);
	this->cursorText.setFillColor(Color::White);
	
}
void EditorState::InitVal()
{
	this->camSpeed = 100.f;
	this->texRect = IntRect(0, 0, static_cast<int>(this->stateData->gridSize), 
		static_cast<int>(this->stateData->gridSize));
	this->collision = false;
	this->type = TileType::DEFAULT;
}
void EditorState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
	this->keybinds["COLLISION"] = this->supportedKeys->at("C");
	this->keybinds["TYPE+"] = this->supportedKeys->at("UP");
	this->keybinds["TYPE-"] = this->supportedKeys->at("DOWN");
	this->keybinds["CAM_UP"] = this->supportedKeys->at("W");
	this->keybinds["CAM_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["CAM_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["CAM_RIGHT"] = this->supportedKeys->at("D");
}
void EditorState::InitFont()
{
	//load font
	if (font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF")) {
		cout << "Editor: Font loaded!" << endl;
	}
	else {
		cout << "Editor: Font failed to load!" << endl;
	}
}
void EditorState::InitButton()
{
	//setting up buttons
	
}
void EditorState::InitBackground()
{

}
void EditorState::InitPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->AddButton("QUIT", 800.f, "Quit");
	this->pauseMenu->AddButton("SAVE", 600.f, "Save");
	this->pauseMenu->AddButton("LOAD", 500.f, "Load");
}
void EditorState::InitGui()
{
	this->sidebar.setSize(Vector2f(80, 1080));
	this->sidebar.setFillColor(Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);
	this->selectorRect.setSize(Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(Color(209, 222, 209,150));
	this->selectorRect.setOutlineThickness(1.0f);
	this->selectorRect.setOutlineColor(Color::Green);

	//preview
	this->selectorRect.setTexture(this->tileMap->GetTileSheet());
	this->selectorRect.setTextureRect(this->texRect);

	//texture selector
	this->texSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->stateData->gridSize, 
		this->tileMap->GetTileSheet(),this->font,"Hide");
}
void EditorState::InitTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10, "Assets/Map/tilesheettest.png");
}
//--------------------------------INITIALIZE------------------------------------------

//------------------------------------FUNCTION----------------------------------------
void EditorState::Update(const float& deltaTime)
{
	//it is w it is
	this->UpdateMousePos(&this->view);

	//for pause menu
	this->UpdatekeyTime(deltaTime);

	//handle input by keyboard
	this->UpdateInput(deltaTime);

	if (this->pause == false) { // unpause
		
		//update states of buttons
		this->UpdateButton();
		//for GUI
		this->UpdateGui(deltaTime);
		//for functionalties
		this->UpdateEditorInput(deltaTime);
	}
	else { //when in pause menu
		this->pauseMenu->Update(this->mousePosWindow);
		this->UpdatePauseMenuButton();
	}

	
}
void EditorState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}
	target->setView(this->view);

	//render map things
	this->tileMap->Render(*target);
	
	target->setView(this->window->getDefaultView());

	//render GUI things
	this->RenderButtons(*target);
	this->RenderGui(*target);

	//=======================================
	//pause
	if (this->pause == true) {  
		this->pauseMenu->Render(*target);
	}
}
void EditorState::RenderGui(RenderTarget& target)
{
	if (!this->texSelector->GetActive()) {
		target.draw(this->selectorRect);
	}
	this->texSelector->Render(target);
	target.draw(this->cursorText);
	target.draw(this->sidebar);
}
void EditorState::UpdateInput(const float& deltaTime)
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
void EditorState::UpdateButton()
{
	//this how to loop thru all elements in a map?
	//Update mouse
	for (auto& it : this->buttons) {
		it.second->Update(this->mousePosWindow);
	}
}
void EditorState::UpdateGui(const float& deltaTime)
{
	//texture selector
	this->texSelector->Update(this->mousePosWindow,deltaTime);
	if (!this->texSelector->GetActive()) {
		//update for the preview tile
		this->selectorRect.setTextureRect(this->texRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,
			this->mousePosGrid.y * this->stateData->gridSize); //this for the actual pos
	}

	//set pos 4 the below
	this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y + 50.f);

	//show coordinates & index of the tiles on the tilesheet
	stringstream ss;
	ss << this->mousePosView.x << " _ " << this->mousePosView.y << endl << //mouse pos with respect to camera
		this->mousePosGrid.x << " _ " << this->mousePosGrid.y << endl <<
		this->texRect.left << " _ " << this->texRect.top << endl << 
		"collision: " << this->collision << endl <<
		"type: "<<this->type << endl;
	this->cursorText.setString(ss.str());

	
}
void EditorState::UpdateEditorInput(const float deltaTime)
{
	//camera movement
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_RIGHT"))))
	{
		this->view.move(this->camSpeed*deltaTime,0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_LEFT"))))
	{
		this->view.move(-this->camSpeed * deltaTime, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_UP"))))
	{
		this->view.move(0.f,-this->camSpeed * deltaTime);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_DOWN"))))
	{
		this->view.move(0.f, this->camSpeed * deltaTime);
	}

	//add tiles
	if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime()) {
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(this->mousePosWindow))) {
			if (!this->texSelector->GetActive()) {
				//add
				this->tileMap->AddTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->texRect, this->collision,this->type);
			}
			else {
				this->texRect = this->texSelector->GetTexRect();
			}
		}
	}
	//remove
	else if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime()) {
		if (!this->sidebar.getGlobalBounds().contains(Vector2f(this->mousePosWindow))) {
			if (!this->texSelector->GetActive()) {
				//remove
				this->tileMap->RemoveTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
			}
		}
	}

	//toggle collision
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("COLLISION"))) && this->GetKeyTime()) {
		if (this->collision == false) {
			this->collision = true;
		}
		else {
			this->collision = false;
		}

	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("TYPE+"))) && this->GetKeyTime()) {
		this->type++;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("TYPE-"))) && this->GetKeyTime()) {
		if (this->type > 0) {
			this->type--;	
		}
	}
}
void EditorState::RenderButtons(RenderTarget& target)
{
	//this how to loop thru all elements in a map?
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}
void EditorState::UpdatePauseMenuButton()
{
	//in pause menu
	if (this->pauseMenu->IsButtonPressed("QUIT")) {
		this->EndState();
	}
	if (this->pauseMenu->IsButtonPressed("SAVE")) {
		this->tileMap->SaveToFile("text.map");
	}
	if (this->pauseMenu->IsButtonPressed("LOAD")) {
		this->tileMap->LoadFromFile("text.map");
	}
}
//------------------------------------FUNCTION----------------------------------------