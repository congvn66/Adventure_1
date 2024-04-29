#pragma once
#include "State.h"
#include "Gui.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingState.h"
#include "GameOverState.h"

class MainMenuState :
    public State
{
private:
    //menu
    RectangleShape background;

    //button elements
    Font font;
    map<string, gui::Button*> buttons;
    Texture texture;

    //init
    void InitVal();
    void InitBackground();
    void InitKeybinds();
    void InitFont();
    void InitButton();
public:
    //constructor, deconstructor
    MainMenuState(StateData* stateData);
    ~MainMenuState();

    //just look in cpp file.
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderButtons(RenderTarget& target);
};

