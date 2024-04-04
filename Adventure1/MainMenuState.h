#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"

class MainMenuState :
    public State
{
private:
    //menu
    RectangleShape background;

    //button elements
    Font font;
    map<string, Button*> buttons;
    Texture texture;

    //init
    void InitVal();
    void InitBackground();
    void InitKeybinds();
    void InitFont();
    void InitButton();
public:
    //constructor, deconstructor
    MainMenuState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~MainMenuState();

    //just look in cpp file.
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderButtons(RenderTarget* target = nullptr);
};

