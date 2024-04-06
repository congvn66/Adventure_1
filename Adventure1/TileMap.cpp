#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned> (gridSizeF);
	this->maxSize.x = 10;
	this->maxSize.y = 10;
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	// add to column (x axis)
	for (size_t x = 0; x < this->maxSize.x; x++) {
		this->map.push_back(vector<vector<Tile>>());
		for (size_t y = 0; y < this->maxSize.y; y++) {
			//add in component for the "x factor" (y axis based on x axis)
			this->map[x].push_back(vector<Tile>());

			//add in componet for the [x][y] factor (2.5D?)
			for (size_t z = 0; z < this->layers; z++) {
				this->map[x][y].push_back(Tile(x*gridSizeF, y * gridSizeF, gridSizeF));
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::Update()
{
}

void TileMap::Render(RenderTarget& target)
{
	for (auto &x : this->map) {
		for (auto &y : x) {
			for (auto& z : y) {
				z.Render(target);
			}
		}
	}
}
