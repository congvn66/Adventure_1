#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned> (gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->map.resize(this->maxSize.x, vector<vector<Tile*>>());
	// add to column (x axis)
	for (size_t x = 0; x < this->maxSize.x; x++) {
		for (size_t y = 0; y < this->maxSize.y; y++) {
			//add in component for the "x factor" (y axis based on x axis)
			this->map[x].resize(this->maxSize.x, vector<Tile*>());

			//add in component for the [x][y] factor (2.5D?)
			for (size_t z = 0; z < this->layers; z++) {
				//create slots
				this->map[x][y].resize(this->layers,nullptr);
			}
		}
	}
	if (this->tileSheet.loadFromFile("Assets/Map/tilesheettest.png")) {
		cout << "Tile map: tile sheet loaded!" << endl;
	}
}

TileMap::~TileMap()
{
	//avoid memory leak
	for (size_t x = 0; x < this->maxSize.x; x++) {
		for (size_t y = 0; y < this->maxSize.y; y++) {
			for (size_t z = 0; z < this->layers; z++) {
				delete this->map[x][y][z];
			}
		}
	}
}

void TileMap::Update()
{
}

void TileMap::Render(RenderTarget& target)
{
	for (auto &x : this->map) {
		for (auto &y : x) {
			for (auto* z : y) {
				//only render if there is a tile
				if (z != nullptr) {
					z->Render(target);
				}
			}
		}
	}
}

const Texture* TileMap::GetTileSheet() const
{
	return &this->tileSheet;
}

void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect texRect) //indexes
{
	//take index from the mousePosGrid, then add to that position 
	// if the array alowed (mouse in the size of the array || only can place in size)

	//check if cursor in size
	if (x < this->maxSize.x && x>=0 
		&& y>=0 &&this->maxSize.y 
		&& z<this->layers &&z>=0) {
		if (this->map[x][y][z] == nullptr) { //if has nothing
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileSheet, texRect);
			cout << "added Tiles!" << endl;
		}
	}
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
	//take index from the mousePosGrid, then remove that tile at position 
	// if the array alowed (mouse in the size of the array || only can remove in size)

	//check if cursor in size
	if (x < this->maxSize.x && x >= 0
		&& y >= 0 && this->maxSize.y
		&& z < this->layers && z >= 0) {
		if (this->map[x][y][z] != nullptr) { //if has something
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
			cout << "remove Tiles!" << endl;
		}
	}
}
