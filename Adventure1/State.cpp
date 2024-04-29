#include "stdafx.h"
#include "State.h"

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->states = stateData->states;
	this->quit = false;
	this->pause = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
	this->gridSize = stateData->gridSize;
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
void State::UpdatekeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax) {
		this->keyTime += 100.f * dt;
	}
}
const bool& State::GetQuit() const
{
	// TODO: insert return statement here
	return this->quit;
}
const bool State::GetKeyTime()
{
	if (this->keyTime >= this->keyTimeMax) {
		this->keyTime = 0.f;
		return true;
	}
	return false;
}
void State::UpdateMousePos(View* view)
{
	//get mouse pos
	this->mousePosScreen = Mouse::getPosition();
	this->mousePosWindow = Mouse::getPosition(*this->window);
	if (view) {
		this->window->setView(*view);
	}
	this->mousePosView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));
	this->mousePosGrid =
		Vector2i(static_cast<int>(this->mousePosView.x)/static_cast<int>(this->stateData->gridSize),
		static_cast<int>(this->mousePosView.y)/ static_cast<int>(this->stateData->gridSize));
	//this for the index in the grid
	this->window->setView(this->window->getDefaultView());
}
