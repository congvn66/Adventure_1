#include "stdafx.h"
#include "EditorState.h"
//---------------------------------CON & DE-------------------------------------------
EditorState::EditorState(RenderWindow* window, std::map <string, int>* supportedKeys, stack <State*>* states)
	:State(window, supportedKeys, states)
{
	this->InitVal();
	this->InitBackground();
	this->InitFont();
	this->InitKeybinds();
	this->InitPauseMenu();
	this->InitButton();
}
EditorState::~EditorState()
{
	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->pauseMenu;
}
//---------------------------------CON & DE-------------------------------------------

//--------------------------------INITIALIZE------------------------------------------
void EditorState::InitVal()
{
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
	//render buttons
	this->RenderButtons(*target);

	this->map.Render(*target);

	if (this->pause == true) {
		this->pauseMenu->Render(*target);
	}
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