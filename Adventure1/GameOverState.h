#pragma once
#include "State.h"
#include "Gui.h"
class GameOverState :
    public State
{
private:
    //menu

    //button elements
    Font font;
    map<string, gui::Button*> buttons;
    Texture texture;

    //init
    void InitVal();

    void InitKeybinds();
    void InitFont();
    void InitButton();
public:
    //constructor, deconstructor
    GameOverState(StateData* stateData);
    ~GameOverState();

    //just look in cpp file.
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderButtons(RenderTarget& target);
};

