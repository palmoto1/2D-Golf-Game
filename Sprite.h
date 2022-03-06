#ifndef SPRITE_H
#define SPRITE_H
#include "Component.h"
#include "Transform.h"
#include <SDL.h>


/*allowing an entity to have a sprite*/

class Sprite : public Component
{

public:


	Sprite();
	Sprite(const std::string& id);


	void initialize() override;
	void update() override;
	void draw() override;

	void setTexture(const std::string& id);

	~Sprite();

private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect desRect;


};

#endif

