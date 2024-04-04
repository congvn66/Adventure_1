#pragma once
#include "State.h"

class GameState :
    public State
{
private:
    Entity player;

    void InitKeybinds();
public:
    //ok, basic things that a state must have:
    GameState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~GameState();

    void Update(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
    void UpdateInput(const float& deltaTime);
};

