#pragma once

#include "GameState.h"

using namespace sf;
using namespace std;

class Game
{
private:
	//variables
	RenderWindow* window;
	Event event;
	float deltaTime;
	Clock clock;


	// just like powerpoint presentation, 
	// for ex: if u click "Exit" the GameState 
	// will be pop out and reveal other States
	stack <State*> states; 

	//init
	void InitWindow();
	void InitStates();

public:
	//constructor & deconstructor
	Game();
	~Game();

	void UpdateDeltaTime();

	//right now this just the event loop.
	void Update();

	//tf this same with Draw;
	void Render();

	//contain game loop
	void Run();

	//contain event loop
	void UpdateSFMLEvent();
};

