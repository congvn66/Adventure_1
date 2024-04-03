#pragma once

//to know more about state: https://www.youtube.com/watch?v=-ZP2Xm-mY4E&ab_channel=TheShaggyDev
#include "Entity.h"
//ok, state is just state, it is what it is, but each "factor" of the
//game will have 1 or more "state", just click 1 state to see
class State
{
protected:
	RenderWindow* window; // ok this is the target 
	map <string, int>* supportedKeys; // point to the supported keys in game.h
	map <string, int> keybinds; // keybinds: what happen if i click this key?
	bool quit;

	vector <Texture*> textures; // what this state look like

	virtual void InitKeybinds() = 0;
public:
	State(RenderWindow* window, map <string,int>* supportedKeys);
	~State();

	virtual void EndState() = 0;
	virtual void CheckQuit() ; // i dont know wut 2 do w/ dis
	virtual void Update(const float& deltaTime) = 0; //update the state with some input.
	virtual void Render(RenderTarget* target=nullptr) = 0; // draw the state on window (by default) on sth else if u want
	const bool& GetQuit() const;
	virtual void UpdateInput(const float& deltaTime) = 0;
};

