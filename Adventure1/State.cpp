#include "State.h"

State::State(RenderWindow* window)
{
	this->window = window;
	this->quit = false;
}

State::~State()
{
}

void State::CheckQuit()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		this->quit = true;
	}
}

const bool& State::GetQuit() const
{
	// TODO: insert return statement here
	return this->quit;
}
