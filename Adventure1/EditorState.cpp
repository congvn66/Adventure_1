#include "stdafx.h"
#include "EditorState.h"
//---------------------------------CON & DE-------------------------------------------
EditorState::EditorState(StateData* stateData)
	:State(stateData)
{
	this->InitVal();
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
void EditorState::InitText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(20);
	this->cursorText.setFillColor(Color::White);
	
}
void EditorState::InitVal()
{
	this->texRect = IntRect(0, 0, static_cast<int>(this->stateData->gridSize), 
		static_cast<int>(this->stateData->gridSize));
}
void EditorState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
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
}
void EditorState::InitGui()
{
	this->selectorRect.setSize(Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selectorRect.setFillColor(Color(209, 222, 209,150));
	this->selectorRect.setOutlineThickness(1.0f);
	this->selectorRect.setOutlineColor(Color::Green);

	//preview
	this->selectorRect.setTexture(this->tileMap->GetTileSheet());
	this->selectorRect.setTextureRect(this->texRect);

	//texture selector
	this->texSelector = new gui::TextureSelector(20.f, 20.f, 500.f, 500.f, this->tileMap->GetTileSheet());
}
void EditorState::InitTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}
//--------------------------------INITIALIZE------------------------------------------

//------------------------------------FUNCTION----------------------------------------
void EditorState::Update(const float& deltaTime)
{
	//it is w it is
	this->UpdateMousePos();

	//for pause menu
	this->UpdatekeyTime(deltaTime);

	//handle input by keyboard
	this->UpdateInput(deltaTime);

	if (this->pause == false) { // unpause
		
		//update states of buttons
		this->UpdateButton();
		//for GUI
		this->UpdateGui();
		//for functionalties
		this->UpdateEditorInput(deltaTime);
	}
	else { //when in pause menu
		this->pauseMenu->Update(this->mousePosView);
		this->UpdatePauseMenuButton();
	}

	
}
void EditorState::Render(RenderTarget* target)
{
	if (target == nullptr) {
		target = this->window;
	}

	//render map things
	this->tileMap->Render(*target);
	

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
	target.draw(this->selectorRect);
	this->texSelector->Render(target);
	target.draw(this->cursorText);
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
		it.second->Update(this->mousePosView);
	}
}
void EditorState::UpdateGui()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize,
		this->mousePosGrid.y * this->stateData->gridSize); //this for the actual pos

	//set pos 4 the below
	this->cursorText.setPosition(this->mousePosView.x + 100.f, this->mousePosView.y + 50.f);

	//show coordinates & index of the tiles on the tilesheet
	stringstream ss;
	ss << this->mousePosView.x << " _ " << this->mousePosView.y << endl << //mouse pos with respect to camera
		this->mousePosGrid.x << " _ " << this->mousePosGrid.y << endl <<
		this->texRect.left << " _ " << this->texRect.top;
	this->cursorText.setString(ss.str());

	//update for the preview tile
	this->selectorRect.setTextureRect(this->texRect);

	//texture selector
	this->texSelector->Update();
}
void EditorState::UpdateEditorInput(const float deltaTime)
{
	//add tiles
	if (Mouse::isButtonPressed(Mouse::Left) && this->GetKeyTime()) {
		//add
		this->tileMap->AddTile(this->mousePosGrid.x, this->mousePosGrid.y,0, this->texRect);
	}
	//remove
	else if (Mouse::isButtonPressed(Mouse::Right) && this->GetKeyTime()) {
		//remove
		this->tileMap->RemoveTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}

	//change texture
	if (Keyboard::isKeyPressed(Keyboard::Right) && this->GetKeyTime()) {
		if (this->texRect.left < 100) {
			this->texRect.left += 100;
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
}
//------------------------------------FUNCTION----------------------------------------