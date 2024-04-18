#include "stdafx.h"
#include "Game.h"

//init func
void Game::InitWindow()
{
	this->fullscreen = true;
	this->settings.antialiasingLevel = this->AALevel;
	if (this->fullscreen) {
		this->window = new RenderWindow(VideoMode(1920, 1080), "Adventure 1", Style::Fullscreen, settings);
	}
	else {
		this->window = new RenderWindow(VideoMode(1920, 1080), "Adventure 1", Style::Titlebar |Style :: Close, settings);
	}
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}
void Game::InitVal()
{
	//only once per app starts.
	this->videoModes = VideoMode::getFullscreenModes();
	this->fullscreen = false;
	bool verticalSync = false;
	unsigned AALevel = 0;
	this->gridSize = 64.f;
}
void Game::InitStates()
{
	//only once per app starts.
	/*this->states.push(new GameState(this->window, &this->supportedKeys));*/
	this->states.push(new MainMenuState(&this->stateData));
}
void Game::InitKeys()
{
	//add supported keys
	this->supportedKeys["A"] = Keyboard::Key::A;
	this->supportedKeys["S"] = Keyboard::Key::S;
	this->supportedKeys["D"] = Keyboard::Key::D;
	this->supportedKeys["W"] = Keyboard::Key::W;
	this->supportedKeys["ESC"] = Keyboard::Key::Escape;
	this->supportedKeys["UP"] = Keyboard::Key::Up;
	this->supportedKeys["DOWN"] = Keyboard::Key::Down;
	this->supportedKeys["C"] = Keyboard::Key::C;
	this->supportedKeys["Z"] = Keyboard::Key::Z;
}

void Game::InitStateData()
{
	this->stateData.window = this->window;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

Game::Game()
{
	this->InitVal();
	this->InitWindow();
	this->InitKeys();
	this->InitStateData();
	this->InitStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

void Game::UpdateDeltaTime()
{
	//update deltaTime
	this->deltaTime = this->clock.restart().asSeconds();

}

void Game::Update()
{
	this->UpdateSFMLEvent();
	if (!this->states.empty()) { 
		if(this->window->hasFocus())
		{ 
			this->states.top()->Update(this->deltaTime);

			//check 4 quit
			if (this->states.top()->GetQuit()) {
				this->states.top()->EndState();
				delete this->states.top();
				this->states.pop();
			}
		}
		
	}
	//close application
	else {
		this->window->close();
	}
}

void Game::Render()
{
	this->window->clear();

	//render things
	if (!this->states.empty()) {
		this->states.top()->Render();
	}
	this->window->display();
}

//core
void Game::Run()
{
	while (this->window->isOpen()) {
		//update deltatime each loop
		this->UpdateDeltaTime();

		this->Update();
		this->Render();
	}
}

void Game::UpdateSFMLEvent()
{
	while (this->window->pollEvent(this->event)){
		if (this->event.type == Event::Closed) {
			this->window->close();
		}
	}
}
