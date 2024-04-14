#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* stateData)
	:State(stateData)
{
	this->InitVal();
	this->InitFont();
	this->InitKeybinds();
	this->InitButton();
	this->InitBackground();
}

void MainMenuState::InitVal()
{
}

void MainMenuState::InitBackground()
{
	this->background.setSize(Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	if (this->texture.loadFromFile("Assets/Image/Background/mainmenubackground.jpg")) {
		cout << "Main menu: background loaded!" << endl;
		this->background.setTexture(&this->texture);
	}
	else {
		cout << "Main menu: background failed to load!";
	}
}

void MainMenuState::InitKeybinds()
{
	this->keybinds["CLOSE"] = this->supportedKeys->at("ESC");
}

void MainMenuState::InitFont()
{	
	//load font
	if (font.loadFromFile("Assets/Font/ARCADECLASSIC.TTF")) {
		cout << "Main menu: Font loaded!" << endl;
	}
	else {
		cout << "Main menu: Font failed to load!" << endl;
	}
}

void MainMenuState::InitButton()
{
	//setting up buttons
	this->buttons["GAME"] = new gui::Button(850, 436, 120.f, 60.f,
		&this->font, "New Game", Color::Transparent, Color::Transparent,Color::Transparent,
		Color::Black,Color::White,Color::White);
	this->buttons["EDITOR"] = new gui::Button(850, 436 + 60, 120.f, 60.f,
		&this->font, "Editor", Color::Transparent, Color::Transparent, Color::Transparent, Color::Black, Color::White, Color::White);
	this->buttons["DUMDUM"] = new gui::Button(850, 436 + 120, 120.f, 60.f,
		&this->font, "Dum Dum", Color::Transparent, Color::Transparent, Color::Transparent, Color::Black, Color::White, Color::White);
	this->buttons["QUIT"] = new gui::Button(850, 436 + 180, 120.f, 60.f,
		&this->font, "Quit", Color::Transparent, Color::Transparent, Color::Transparent, Color::Black, Color::White, Color::White);
}

MainMenuState::~MainMenuState()
{

	//just delete buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::Update(const float& deltaTime)
{
	//it is w it is
	this->UpdateMousePos();

	//handle input by keyboard
	this->UpdateInput(deltaTime);

	//update states of buttons
	this->UpdateButton();
}

void MainMenuState::Render(RenderTarget* target)
{
	//render menu
	if (target == nullptr) {
		target = this->window;
	}
	target->draw(this->background);

	//render buttons
	this->RenderButtons(*target);
}

void MainMenuState::UpdateInput(const float& deltaTime)
{
}

void MainMenuState::UpdateButton()
{
	//this how to loop thru all elements in a map?
	//Update mouse
	for (auto &it : this->buttons) {
		it.second->Update(this->mousePosWindow);
	}

	//check for quit?
	if (this->buttons["QUIT"]->IsPressed()) {
		this->EndState();
	}

	//editor
	if (this->buttons["EDITOR"]->IsPressed()) {
		this->states->push(new EditorState(this->stateData));
	}

	//setting
	if (this->buttons["DUMDUM"]->IsPressed()) {
		this->states->push(new SettingState(this->stateData));
	}

	//new game
	if (this->buttons["GAME"]->IsPressed()) {
		this->states->push(new GameState(this->stateData));
	}
}

void MainMenuState::RenderButtons(RenderTarget& target)
{
	//this how to loop thru all elements in a map?
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}
