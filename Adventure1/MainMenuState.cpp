#include "MainMenuState.h"

MainMenuState::MainMenuState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states)
	:State(window,supportedKeys, states)
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
	this->background.setSize(Vector2f(this->window->getSize().x, this->window->getSize().y));
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
	this->buttons["GAME"] = new Button(850, 436, 120.f, 60.f,
		&this->font, "New Game", Color::Transparent, Color::Transparent, Color::Transparent);
	this->buttons["EDITOR"] = new Button(850, 436 + 60, 120.f, 60.f,
		&this->font, "Editor", Color::Transparent, Color::Transparent, Color::Transparent);
	this->buttons["OPTION"] = new Button(850, 436 + 120, 120.f, 60.f,
		&this->font, "Option", Color::Transparent, Color::Transparent, Color::Transparent);
	this->buttons["QUIT"] = new Button(850, 436 + 180, 120.f, 60.f,
		&this->font, "Quit", Color::Transparent, Color::Transparent, Color::Transparent);
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
	this->RenderButtons(target);
}

void MainMenuState::UpdateInput(const float& deltaTime)
{
}

void MainMenuState::UpdateButton()
{
	//this how to loop thru all elements in a map?
	//Update mouse
	for (auto &it : this->buttons) {
		it.second->Update(this->mousePosView);
	}

	//check for quit?
	if (this->buttons["QUIT"]->IsPressed()) {
		this->EndState();
	}

	//editor
	if (this->buttons["EDITOR"]->IsPressed()) {
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}

	//new game
	if (this->buttons["GAME"]->IsPressed()) {
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}
}

void MainMenuState::RenderButtons(RenderTarget* target)
{
	//this how to loop thru all elements in a map?
	for (auto& it : this->buttons) {
		it.second->Render(target);
	}
}
