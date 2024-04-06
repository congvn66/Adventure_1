#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h";
#include "TileMap.h"

using namespace gui;

class EditorState :
    public State
{
private:

    TileMap map;

    PauseMenu* pauseMenu;
    //button elements
    Font font;
    std::map<string, Button*> buttons;

    //init
    void InitVal();
    void InitKeybinds();
    void InitFont();
    void InitButton();
    void InitBackground();
    void InitPauseMenu();
public:
    //constructor, deconstructor
    EditorState(RenderWindow* window, std::map <string, int>* supportedKeys, stack <State*>* states);
    ~EditorState();

    //just look in cpp file.
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderButtons(RenderTarget& target);
    void UpdatePauseMenuButton();
};

