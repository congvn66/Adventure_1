#pragma once

#include "Entity.h"
class State;
class StateData {
public:
	StateData() {

	}
	//val
	float gridSize;
	RenderWindow* window; 
	map <string, int>* supportedKeys;
	stack <State*>* states;
};
//to know more about state: https://www.youtube.com/watch?v=-ZP2Xm-mY4E&ab_channel=TheShaggyDev
//ok, state is just state, it is what it is, but each "factor" of the
//game will have 1 or more "state", just click 1 state to see
class State
{
protected:
	StateData* stateData;
	stack <State*>* states; // a pointer to a stack full of state pointers
	RenderWindow* window; // ok this is the target 
	map <string, int>* supportedKeys; // point to the supported keys in game.h
	map <string, int> keybinds; // keybinds: what happen if i click this key?

	bool quit; // check to escape this state?
	bool pause; //check for pause
	float keyTime;
	float keyTimeMax;
	float gridSize;

	//mouse pos
	Vector2i mousePosScreen;
	Vector2i mousePosWindow;
	Vector2f mousePosView;
	Vector2i mousePosGrid; // which grid are u on?

	map <string,Texture> textures; //the textures that this state contain

	virtual void InitKeybinds() = 0;
public:
	State(StateData* stateData);
	~State();

	void EndState();//end the state
	void PauseState(); // pause the state
	void UnpauseState(); // same

	const bool& GetQuit() const;
	const bool GetKeyTime();

	virtual void Update(const float& deltaTime) = 0; //update the state with some input.
	virtual void UpdatekeyTime(const float& dt);
	virtual void Render(RenderTarget* target=nullptr) = 0; // draw the state on window (by default) on sth else if u want
	virtual void UpdateInput(const float& deltaTime) = 0;
	virtual void UpdateMousePos(View* view = nullptr);
};

