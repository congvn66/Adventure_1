#pragma once

#include "EditorMode.h"

class EditorMode;
class State;
class StateData;
class Tile;
class TileMap;

class DefaultMode :
    public EditorMode
{
private:
    Text cursorText; //i4
    RectangleShape sidebar; //sidebar
    gui::TextureSelector* texSelector; //tiles list
    RectangleShape selectorRect; // cursor in editor?
    IntRect texRect;
    bool collision;
    short type;

    int layer;
    bool tileAddLock;

    void InitVal();
    void InitGui();
public:
    DefaultMode(StateData* stateData, TileMap* tileMap, Font* font);
    ~DefaultMode();

    void UpdateInput(const float& deltaTime);
    void UpdateGui(const float& deltaTime);
    void Update(const float& deltaTime);

    void Render(RenderTarget* target = nullptr) ;
    void RenderGui(RenderTarget& target) ;
};

