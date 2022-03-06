#include "AssetManager.h"



AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {
	textures.clear();
	fonts.clear();

}

void AssetManager::addTexture(const std::string& textureId, const char* path, bool transparent, int red, int green, int blue) {
	textures.emplace(textureId, TextureManager::load(path, transparent, red, green, blue));

}

SDL_Texture* AssetManager::getTexture(const std::string& textureId) {
	return textures[textureId];
}

void AssetManager::addFont(const std::string& fontId, const char* path, int size)
{
	fonts.emplace(fontId, TTF_OpenFont(path, size));
}

TTF_Font* AssetManager::getFont(const std::string& fontId)
{
	return fonts[fontId];
}
