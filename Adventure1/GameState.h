#pragma once
#include "State.h"


//i think of 2 states: on & off =))
class GameState :
    public State
{
private:
    Entity player;
public:
    //ok, basic things that a state must have:
    GameState(RenderWindow* window);
    ~GameState();

    void EndState();
    void Update(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
    void UpdateKeybinds(const float& deltaTime);
};

