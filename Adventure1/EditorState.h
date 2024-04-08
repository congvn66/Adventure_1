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
    //tile shit
    TileMap* tileMap;
    RectangleShape selectorRect; // cursor in editor?
    IntRect texRect;
    Text cursorText;
    gui::TextureSelector* texSelector;
    RectangleShape sidebar;

    //pmenu
    PauseMenu* pauseMenu;

    //button elements
    Font font;
    std::map<string, Button*> buttons;

    //init
    void InitText();
    void InitVal();
    void InitKeybinds();
    void InitFont();
    void InitButton();
    void InitBackground();
    void InitPauseMenu();
    void InitGui();
    void InitTileMap();
public:
    //constructor, deconstructor
    EditorState(StateData* stateData);
    ~EditorState();

    //just look in cpp file.
    void UpdateGui(const float& deltaTime);
    void UpdateEditorInput(const float deltaTime);
    void Update(const float& deltaTime);
    void UpdateInput(const float& deltaTime);
    void UpdateButton();
    void Render(RenderTarget* target = nullptr);
    void RenderGui(RenderTarget& target);
    void RenderButtons(RenderTarget& target);
    void UpdatePauseMenuButton();
};

