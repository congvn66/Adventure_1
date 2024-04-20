#include "stdafx.h"
#include "EditorMode.h"

EditorMode::EditorMode(StateData* stateData, TileMap* tileMap, EditorStateData* editorStateData)
	:stateData(stateData), tileMap(tileMap), editorStateData(editorStateData)
{
}

EditorMode::~EditorMode()
{
}

const bool EditorMode::GetKeyTime()
{
	if (*this->editorStateData->keyTime >= *this->editorStateData->keyTimeMax) {
		*this->editorStateData->keyTime = 0.f;
		return true;
	}
	return false;
}