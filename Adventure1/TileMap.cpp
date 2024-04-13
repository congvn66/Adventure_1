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

TileMap::TileMap(float gridSize, int width, int height, string texFile)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int> (gridSizeF);
	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;

	//Assets/Map/tilesheettest.png
	this->texFile = texFile;

	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeGrid.x, vector<vector<Tile*>>());
	// add to column (x axis)
	for (int x = 0; x < this->maxSizeGrid.x; x++) {
		for (int y = 0; y < this->maxSizeGrid.y; y++) {
			//add in component for the "x factor" (y axis based on x axis)
			this->map[x].resize(this->maxSizeGrid.x, vector<Tile*>());

			//add in component for the [x][y] factor (2.5D?)
			for (int z = 0; z < this->layers; z++) {
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
	this->collisionBox.setOutlineThickness(2.f);
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
	if (entity)
	{
		this->layer = 0;
		this->fromX = entity->getGridPos(this->gridSizeI).x - 3;
		if (this->fromX < 0)
		{
			this->fromX = 0;
		}
		else if (this->fromX >= this->maxSizeGrid.x)
		{
			this->fromX = this->maxSizeGrid.x;
		}
		this->toX = entity->getGridPos(this->gridSizeI).x + 8;
		if (this->toX < 0)
		{
			this->toX = 0;
		}
		else if (this->toX >= this->maxSizeGrid.x)
		{
			this->toX = this->maxSizeGrid.x;
		}
		this->fromY = entity->getGridPos(this->gridSizeI).y - 3;
		if (this->fromY < 0)
		{
			this->fromY = 0;
		}
		else if (this->fromY >= this->maxSizeGrid.y)
		{
			this->fromY = this->maxSizeGrid.y;
		}
		this->toY = entity->getGridPos(this->gridSizeI).y + 8;
		if (this->toY < 0)
		{
			this->toY = 0;
		}
		else if (this->toY >= this->maxSizeGrid.y)
		{
			this->toY = this->maxSizeGrid.y;
		}

		for (int x = this->fromX; x < this->toX; x++) {
			for (int y = this->fromY; y < this->toY; y++) {
				this->map[x][y][this->layer]->Render(target);                                  //
				if (this->map[x][y][this->layer]->GetCollision()) {							   //  only render tiles around player!
					this->collisionBox.setPosition(this->map[x][y][this->layer]->GetPos());    //
					target.draw(this->collisionBox);
				}
			}
		}
	}
	else
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
}
const Texture* TileMap::GetTileSheet() const
{
	return &this->tileSheet;
}
void TileMap::UpdateCollision(Entity* entity, const float& deltaTime)
{
	//check if pass the border
	if (entity->GetPos().x < 0.f) // left border
	{
		entity->SetPos(0.f, entity->GetPos().y);
		entity->StopX();
	}
	else if (entity->GetPos().x +entity->GetGlobalBounds().width> this->maxSizeWorldF.x) // right border
	{
		entity->SetPos(this->maxSizeWorldF.x- entity->GetGlobalBounds().width, entity->GetPos().y);
		entity->StopX();
	}

	if (entity->GetPos().y < 0.f) // up border
	{
		entity->SetPos(entity->GetPos().x, 0.f);
		entity->StopY();
	}
	else if (entity->GetPos().y+entity->GetGlobalBounds().height > this->maxSizeWorldF.y) //down border
	{
		entity->SetPos(entity->GetPos().x, this->maxSizeWorldF.y- entity->GetGlobalBounds().height);
		entity->StopY();
	}


	//check if encounter collisive tiles
	// check tiles around players
	this->fromX = entity->getGridPos(this->gridSizeI).x -1;
	if (this->fromX < 0)
	{
		this->fromX = 0;
	}
	else if (this->fromX >= this->maxSizeGrid.x)
	{
		this->fromX = this->maxSizeGrid.x ;
	}
	this->toX = entity->getGridPos(this->gridSizeI).x +3;
	if (this->toX < 0)
	{
		this->toX = 0;
	}
	else if (this->toX >= this->maxSizeGrid.x)
	{
		this->toX = this->maxSizeGrid.x ;
	}
	this->fromY = entity->getGridPos(this->gridSizeI).y - 1;
	if (this->fromY < 0)
	{
		this->fromY = 0;
	}
	else if (this->fromY >= this->maxSizeGrid.y)
	{
		this->fromY = this->maxSizeGrid.y - 1;
	}
	this->toY = entity->getGridPos(this->gridSizeI).y + 3;
	if (this->toY < 0)
	{
		this->toY = 0;
	}
	else if (this->toY >= this->maxSizeGrid.y)
	{
		this->toY = this->maxSizeGrid.y - 1;
	}

	for (int x = this->fromX; x < this->toX; x++) {
		for (int y = this->fromY; y < this->toY; y++) {
			FloatRect playerBounds = entity->GetGlobalBounds();
			FloatRect wallBounds = this->map[x][y][this->layer]->GetGlobalBounds();
			FloatRect nextPositionBounds = entity->GetNextPosBounds(deltaTime);
			if (this->map[x][y][this->layer]->Intersects(nextPositionBounds)&& this->map[x][y][this->layer]->GetCollision())
			{
				//bottom collision
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top +wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left) {
					entity->StopY();
					entity->SetPos(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				//top collision
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left) {
					entity->StopY();
					entity->SetPos(playerBounds.left, wallBounds.top + wallBounds.height);
				}
				//right collision
				if (playerBounds.left < wallBounds.left
					&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top) {
					entity->StopX();
					entity->SetPos(wallBounds.left - playerBounds.width, playerBounds.top);
				}
				//left collision
				else if (playerBounds.left > wallBounds.left
					&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top) {
					entity->StopX();
					entity->SetPos(wallBounds.left + wallBounds.width, playerBounds.top);
				}
			}
		}
	}

}
void TileMap::AddTile(const int x, const int y, const int z, const IntRect texRect, const bool& collision, const short& type) //indexes
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
void TileMap::RemoveTile(const int x, const int y, const int z)
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
		outFile << this->gridSizeI << endl;
		outFile << this->layers << endl;
		outFile << this->texFile << endl;

		//loop thru all the map.
		for (int x = 0; x < this->maxSizeGrid.x; x++) {
			for (int y = 0; y < this->maxSizeGrid.y; y++) {
				for (int z = 0; z < this->layers; z++) {
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
		Vector2i size;
		int gridSize = 0;
		int layers = 0;
		string texFile = "";
		inFile >> size.x >> size.y >> gridSize >> layers >> texFile;

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeGrid.x = size.x;
		this->maxSizeGrid.y = size.y;
		this->layers = layers;

		//Assets/Map/tilesheettest.png
		this->texFile = texFile;

		this->Clear();

		//specific initializing
		int x = 0;				// |
		int y = 0;				// |
		int z = 0;             // |   
		int trX = 0;			// |     CONTAINER FOR SPECIFIC!
		int trY = 0;			// |
		bool collision = false;		// |
		short type = 0;				// |
		this->map.resize(this->maxSizeGrid.x, vector<vector<Tile*>>());               // |
		// add to column (x axis)												  // |
		for (int x = 0; x < this->maxSizeGrid.x; x++) {							  // |
			for (int y = 0; y < this->maxSizeGrid.y; y++) {						  // |
				//add in component for the "x factor" (y axis based on x axis)    // |     CREATE SLOTS FOR LOADING MAP!
				this->map[x].resize(this->maxSizeGrid.x, vector<Tile*>());			  // |	
				//add in component for the [x][y] factor (2.5D?)				  // |		
				for (int z = 0; z < this->layers; z++) {                       // |
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
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, IntRect(trX, trY, gridSizeI, gridSizeI), collision, type);
		}
	}
	inFile.close();
}
