#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <map>
#include <string>
#include "TextureManager.h"
#include <SDL_ttf.h>


/*class for keeping and managing assets/resourses*/


class AssetManager {
public:
	AssetManager();
	~AssetManager();


	void addTexture(const std::string& textureId, const char* path, bool transparent, int red, int green, int blue);
	SDL_Texture* getTexture(const std::string& textureId);

	void addFont(const std::string& fontId, const char* path, int size);
	TTF_Font* getFont(const std::string& fontId);


private:
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};


#endif
