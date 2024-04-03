#pragma once
#include "State.h"
class MainMenuState :
    public State
{
private:
    RectangleShape background;

    void InitKeybinds();
public:
    MainMenuState(RenderWindow* window, map <string, int>* supportedKeys);
    ~MainMenuState();

    void EndState();
    void Update(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
    void UpdateInput(const float& deltaTime);
};

