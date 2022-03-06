#include "TileMap.h"
#include "Component.h"
#include "Tile.h"
#include "Collider.h"
#include "EntityGroups.h"
#include "Entity.h"
#include "EntityManager.h"
#include "GameEngine.h";
#include "GameManager.h"
#include <fstream>



TileMap::TileMap(int scale, int tSize) : mapScale(scale), tileSize(tSize) {}

TileMap::~TileMap()
{
	
}


// loads a textfile with a matrix on different numbers where every number represents a different id for different types of tiles
void TileMap::loadMap(const std::string& path, int width, int height)
{

	char c;
	std::fstream file;
	file.open(path);


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++) {
			file.get(c);
			int colorId = atoi(&c);
			addTile(j * (tileSize * mapScale), i * (tileSize * mapScale), colorId);
			file.ignore();
		}
	}

	file.close();
}

//numbers in tilemap also decides if a tile should have a collider
void TileMap::addTile(int posX, int posY, int colorId)
{
	auto& tile(GameEngine::gameManager->getEntityManager()->addEntity());
	tile.addComponent<Tile>(posX, posY, tileSize, mapScale, colorId);
	if (colorId == 1) 
		GameEngine::gameManager->createMapCollider("wall", posX, posY, tileSize * mapScale, EntityGroup::WALL_GROUP);
		
	if (colorId == 2) 
		GameEngine::gameManager->createMapCollider("water", posX, posY, tileSize * mapScale, EntityGroup::WATER_GROUP);
	
	GameEngine::gameManager->getEntityManager()->addToEntityGroup(&tile, EntityGroup::TILE_GROUP);
}









