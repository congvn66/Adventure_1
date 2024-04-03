#include "Game.h"



//init func
void Game::InitWindow()
{
	//only once per app starts.
	this->window = new RenderWindow(VideoMode(1920, 1080), "Adventure 1");
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void Game::InitStates()
{
	//only once per app starts.
	this->states.push(new GameState(this->window, &this->supportedKeys));
	this->states.push(new MainMenuState(this->window,&this->supportedKeys));
}

void Game::InitKeys()
{
	//add supported keys
	this->supportedKeys["A"] = Keyboard::Key::A;
	this->supportedKeys["S"] = Keyboard::Key::S;
	this->supportedKeys["D"] = Keyboard::Key::D;
	this->supportedKeys["W"] = Keyboard::Key::W;
	this->supportedKeys["ESC"] = Keyboard::Key::Escape;
}

Game::Game()
{
	this->InitWindow();
	this->InitKeys();
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
		/*cout << this->states.size() << endl;*/
		this->states.top()->Update(this->deltaTime);
		if (this->states.top()->GetQuit()) {
			this->states.top()->EndState();
			delete this->states.top();
			this->states.pop();
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
