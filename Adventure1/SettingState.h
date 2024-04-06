#pragma once
#include "State.h"
#include "Gui.h"

class SettingState :
    public State
{
private:
    //setting
    RectangleShape background;

    //button elements
    Font font;
    map<string, gui::Button*> buttons;
    map<string, gui::DropDownList*> dropdownlist;
    Texture texture;

    //init
    void InitVal();
    void InitBackground();
    void InitKeybinds();
    void InitFont();
    void InitGui();
public:
    SettingState(RenderWindow* window, map <string, int>* supportedKeys, stack <State*>* states);
    ~SettingState();

    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateGui(const float& deltaTime);
    void Render(RenderTarget* target = nullptr);
    void RenderGui(RenderTarget& target);
};

