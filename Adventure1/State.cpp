#include "State.h"

State::State(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
	this->pause = false;
}

State::~State()
{
}

void State::EndState()
{
	this->quit = true;
}

void State::PauseState()
{
	this->pause = true;
}

void State::UnpauseState()
{
	this->pause = false;
}

const bool& State::GetQuit() const
{
	// TODO: insert return statement here
	return this->quit;
}

void State::UpdateMousePos()
{
	//get mouse pos
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
}
