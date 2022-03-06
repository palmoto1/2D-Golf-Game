#ifndef TILE_H
#define TILE_H

#include "Component.h"
#include "Vector.h"
#include <SDL.h>

/*represent an individual tile in the map*/


class Tile : public Component
{
public:


	Tile();
	Tile(int posX, int posY, int size, int scale, int id);

	void draw() override;

	void setTexture(int id);

	~Tile();


private:
	SDL_Texture* texture = nullptr;
	SDL_Rect srcRect;
	SDL_Rect desRect;
	Vector pos;

};


#endif

