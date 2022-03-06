#include "Tile.h"
#include "TextureManager.h"
#include "AssetManager.h"


Tile::Tile() {}


Tile::Tile(int posX, int posY, int size, int scale, int id) {

	setTexture(id);

	srcRect = { 0, 0, size * scale, size * scale };

	pos.x = static_cast<float>(posX);
	pos.y = static_cast<float>(posY);

	desRect = { posX, posY, size * scale, size * scale };

}


void Tile::draw() {
	TextureManager::draw(texture, srcRect, desRect);
}


Tile::~Tile() {

}


//textures on tiles will differ based on number in tilemap matrix
void Tile::setTexture(int id) {

	if (id == 1)
		texture = GameEngine::assetManager->getTexture("wall");
	else if (id == 2)
		texture = GameEngine::assetManager->getTexture("water");
	else
		texture = GameEngine::assetManager->getTexture("grass");

}
