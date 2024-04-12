#include "stdafx.h"
#include "TileMap.h"

void TileMap::Clear()
{
	//avoid memory leak
	for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
		for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
			for (size_t z = 0; z < this->layers; z++) {
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, string texFile)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned> (gridSizeF);
	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;

	//Assets/Map/tilesheettest.png
	this->texFile = texFile;

	this->map.resize(this->maxSizeGrid.x, vector<vector<Tile*>>());
	// add to column (x axis)
	for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
		for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
			//add in component for the "x factor" (y axis based on x axis)
			this->map[x].resize(this->maxSizeGrid.x, vector<Tile*>());

			//add in component for the [x][y] factor (2.5D?)
			for (size_t z = 0; z < this->layers; z++) {
				//create slots
				this->map[x][y].resize(this->layers,nullptr);
			}
		}
	}
	if (this->tileSheet.loadFromFile(this->texFile)) {
		cout << "Tile map: tile sheet loaded!" << endl;
	}
	else {
		cout << "Tile map: tile sheet cant load!" << endl;
	}

	//collision box
	this->collisionBox.setSize(Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}
TileMap::~TileMap()
{
	this->Clear();
}

void TileMap::Update()
{
}
void TileMap::Render(RenderTarget& target, Entity* entity)
{
	for (auto &x : this->map) {
		for (auto &y : x) {
			for (auto* z : y) {
				//only render if there is a tile
				if (z != nullptr) {
					z->Render(target);
					if (z->GetCollision())
					{
						this->collisionBox.setPosition(z->GetPos());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
}
const Texture* TileMap::GetTileSheet() const
{
	return &this->tileSheet;
}
void TileMap::UpdateCollision(Entity* entity)
{
	//check if pass the border
	if (entity->GetPos().x < 0.f) // left border
	{
		entity->SetPos(0.f, entity->GetPos().y);
	}
	else if (entity->GetPos().x > this->maxSizeWorldF.x) // right border
	{
		entity->SetPos(this->maxSizeWorldF.x, entity->GetPos().y);
	}

	if (entity->GetPos().y < 0.f) // up border
	{
		entity->SetPos(entity->GetPos().x, 0.f);
	}
	else if (entity->GetPos().y > this->maxSizeWorldF.y) //down border
	{
		entity->SetPos(entity->GetPos().x, this->maxSizeWorldF.y);
	}


	//check if encounter collisive tiles

}
void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z, const IntRect texRect, const bool& collision, const short& type) //indexes
{
	//take index from the mousePosGrid, then add to that position 
	// if the array alowed (mouse in the size of the array || only can place in size)

	//check if cursor in size
	if (x < this->maxSizeGrid.x && x>=0
		&& y>=0 &&this->maxSizeGrid.y
		&& z<this->layers &&z>=0) {
		if (this->map[x][y][z] == nullptr) { //if has nothing
			this->map[x][y][z] = new Tile(x, y , this->gridSizeF, this->tileSheet, texRect,collision,type);
			cout << "added Tiles!" << endl;
		}
	}
}
void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
	//take index from the mousePosGrid, then remove that tile at position 
	// if the array alowed (mouse in the size of the array || only can remove in size)

	//check if cursor in size
	if (x < this->maxSizeGrid.x && x >= 0
		&& y >= 0 && this->maxSizeGrid.y
		&& z < this->layers && z >= 0) {
		if (this->map[x][y][z] != nullptr) { //if has something
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
			cout << "remove Tiles!" << endl;
		}
	}
}
void TileMap::SaveToFile(const string fileName)
{
	//save tile map to a text file format
	//Format: 
	//General:
	//Size x y
	//gridSize
	// layers
	// texture file dir
	// 
	//Specific:	
	//gridPos x y
	//x(in grid), y(in grid), z(in grid-layer), Texture Rect x y, collision, type????
	ofstream outFile;

	outFile.open(fileName);

	if (outFile) {
		outFile << this->maxSizeGrid.x << " " << this->maxSizeGrid.y << endl;
		outFile << this->gridSizeU << endl;
		outFile << this->layers << endl;
		outFile << this->texFile << endl;

		//loop thru all the map.
		for (size_t x = 0; x < this->maxSizeGrid.x; x++) {
			for (size_t y = 0; y < this->maxSizeGrid.y; y++) {
				for (size_t z = 0; z < this->layers; z++) {
					if (this->map[x][y][z] != nullptr) {
						outFile << x << " " << y << " " << z << " " << this->map[x][y][z]->GetAsString() << " ";//there's still a space =)
					}
				}
			}
		}
	}
	else {
		cout << "Tile Map: cant save map!" << endl;
	}
	outFile.close();
}
void TileMap::LoadFromFile(const string fileName)
{
	ifstream inFile;

	inFile.open(fileName);

	if (inFile) {

		//general loading
		Vector2u size;
		unsigned gridSizeU = 0;
		unsigned layers = 0;
		string texFile = "";
		inFile >> size.x >> size.y >> gridSizeU >> layers >> texFile;

		this->gridSizeF = static_cast<unsigned>(gridSizeU);
		this->gridSizeU = gridSizeU;
		this->maxSizeGrid.x = size.x;
		this->maxSizeGrid.y = size.y;
		this->layers = layers;

		//Assets/Map/tilesheettest.png
		this->texFile = texFile;

		this->Clear();

		//specific initializing
		unsigned x = 0;				// |
		unsigned y = 0;				// |
		unsigned z = 0;             // |   
		unsigned trX = 0;			// |     CONTAINER FOR SPECIFIC!
		unsigned trY = 0;			// |
		bool collision = false;		// |
		short type = 0;				// |
		this->map.resize(this->maxSizeGrid.x, vector<vector<Tile*>>());               // |
		// add to column (x axis)												  // |
		for (size_t x = 0; x < this->maxSizeGrid.x; x++) {							  // |
			for (size_t y = 0; y < this->maxSizeGrid.y; y++) {						  // |
				//add in component for the "x factor" (y axis based on x axis)    // |     CREATE SLOTS FOR LOADING MAP!
				this->map[x].resize(this->maxSizeGrid.x, vector<Tile*>());			  // |	
				//add in component for the [x][y] factor (2.5D?)				  // |		
				for (size_t z = 0; z < this->layers; z++) {                       // |
					//create slots                                                // |
					this->map[x][y].resize(this->layers, nullptr);                // |
				}
			}
		}
		if (this->tileSheet.loadFromFile(this->texFile)) {
			cout << "Tile map: tile sheet loaded!" << endl;
		}
		else {
			cout << "Tile map: tile sheet cant load!" << endl;
		}

		//information taking
		while (inFile >> x >> y >> z >> trX >> trY >> collision >> type) {
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, IntRect(trX, trY, gridSizeU, gridSizeU), collision, type);
		}
	}
	inFile.close();
}
