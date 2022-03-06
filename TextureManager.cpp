#include "TextureManager.h"



SDL_Texture* TextureManager::load(const char* filename, bool transparent, int red, int green, int blue)
{
    SDL_Surface* tempSurface = IMG_Load(filename);

    if (transparent) {
        Uint32 color = SDL_MapRGB(tempSurface->format, red, green, blue);
        SDL_SetColorKey(tempSurface, true, color);
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(GameEngine::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::draw(SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& des)
{
 
    SDL_RenderCopy(GameEngine::renderer, tex, &src, &des);
}
