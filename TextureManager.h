#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include "GameEngine.h"

/*manages textures*/

class TextureManager
{
public:
	static SDL_Texture* load(const char* filename, bool transparent, int red, int green, int blue);
	static void draw(SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& des);

};

#endif

