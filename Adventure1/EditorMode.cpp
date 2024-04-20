#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* stateData, TileMap* tileMap, Font* font)
	:stateData(stateData), tileMap(tileMap), font(font)
{
}

EditorMode::~EditorMode()
{
}
