#include "stdafx.h"
#include "EditorState.h"
//---------------------------------CON & DE-------------------------------------------
EditorState::EditorState(StateData* stateData)
	:State(stateData)
{
	this->InitVal();
	this->InitEditorStateData();
	this->InitView();
	this->InitFont();	
	this->InitKeybinds();
	this->InitPauseMenu();
	this->InitTileMap();
	this->InitButton();
	this->InitGui();
	this->InitMode();
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

	for (size_t i = 0; i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}
//---------------------------------CON & DE-------------------------------------------

//--------------------------------INITIALIZE------------------------------------------
void EditorState::InitView()
{
	this->view.setSize(Vector2f(1920, 1080));
	this->view.setCenter(1920 / 2.f, 1080 / 2.f);
}
void EditorState::InitEditorStateData()
{
	this->editorStateData.keyTime = &this->keyTime;
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keyTimeMax = &this->keyTimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
}
void EditorState::InitVal()
{
	this->camSpeed = 500.f;
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
	this->keybinds["TILE_LOCK"] = this->supportedKeys->at("Z");
	this->keybinds["MODE_UP"] = this->supportedKeys->at("PGUP");
	this->keybinds["MODE_DOWN"] = this->supportedKeys->at("PGDOWN");
	this->keybinds["TYPE_UP"] = this->supportedKeys->at("1");
	this->keybinds["AMOUNT_UP"] = this->supportedKeys->at("2");
	this->keybinds["TTS_UP"] = this->supportedKeys->at("3");
	this->keybinds["MD_UP"] = this->supportedKeys->at("4");
}
void EditorState::InitFont()
{
	//load font
	if (font.loadFromFile("Assets/Font/cour.ttf")) {
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
void EditorState::InitPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->AddButton("QUIT", 800.f, "Quit");
	this->pauseMenu->AddButton("SAVE", 600.f, "Save");
	this->pauseMenu->AddButton("LOAD", 500.f, "Load");
}
void EditorState::InitGui()
{
	

}
void EditorState::InitTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 200, 200, "Assets/Map/newtilesheet.png");
}
void EditorState::InitMode()
{
	this->modes.push_back(new DefaultMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_MODE;
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
		//for modes
		this->UpdateModes(deltaTime);
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

	//render map things
	target->setView(this->view);
	this->tileMap->Render(*target, this->mousePosGrid, true);
	this->tileMap->RenderDefered(*target);
	
	target->setView(this->window->getDefaultView());
	//render GUI things
	this->RenderButtons(*target);
	this->RenderGui(*target);
	this->RenderModes(*target);
	//=======================================
	//pause
	if (this->pause == true) {  
		target->setView(this->window->getDefaultView());
		this->pauseMenu->Render(*target);
	}
}
void EditorState::RenderGui(RenderTarget& target)
{
	
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
void EditorState::UpdateModes(const float& deltaTime)
{
	this->modes[this->activeMode]->Update(deltaTime);
}
void EditorState::RenderModes(RenderTarget& target)
{
	this->modes[this->activeMode]->Render(target);
}
void EditorState::UpdateGui(const float& deltaTime)
{
	

}
void EditorState::UpdateEditorInput(const float deltaTime)
{
	//camera movement
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_RIGHT"))))
	{
		this->view.move(this->camSpeed * deltaTime, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_LEFT"))))
	{
		this->view.move(-this->camSpeed * deltaTime, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_UP"))))
	{
		this->view.move(0.f, -this->camSpeed * deltaTime);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CAM_DOWN"))))
	{
		this->view.move(0.f, this->camSpeed * deltaTime);
	}

	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < this->modes.size() - 1)
		{
			this->activeMode++;
		}
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
		if (this->activeMode > 0)
		{
			this->activeMode--;
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