#include "State.h"

State::State(RenderWindow* window, map <string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->quit = false;
}

State::~State()
{
}

void State::CheckQuit()
{
	if (Keyboard::isKeyPressed(Keyboard::Key(this->keybinds.at("CLOSE")))) {
		this->quit = true;
	}
}

const bool& State::GetQuit() const
{
	// TODO: insert return statement here
	return this->quit;
}
