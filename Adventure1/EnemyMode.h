#pragma once
#include "EditorMode.h"
#include "EnemySpawner.h"

class EnemySpawner;
class EditorMode;
class State;
class StateData;
class Tile;
class TileMap;

class EnemyMode :
    public EditorMode
{
private:
    Text cursorText; //i4
    RectangleShape sidebar; //sidebar
    RectangleShape selectorRect; // cursor in editor?
    IntRect texRect;

    int enemyType;
    int amount;
    int timeToSpawn;
    float maxDis;

    void InitGui();
    void InitVal();
public:
    EnemyMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData);
    ~EnemyMode();

    void UpdateInput(const float& deltaTime);
    void UpdateGui(const float& deltaTime);
    void Update(const float& deltaTime);

    void Render(RenderTarget& target);
    void RenderGui(RenderTarget& target);
};

