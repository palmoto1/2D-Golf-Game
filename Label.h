#ifndef LABEL_H
#define LABEL_H
#include "Component.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


class Label : public Component
{

public:
	Label(int xPos, int yPos, const std::string& t, const std::string& f, const SDL_Color& c);

	~Label();


	std::string getText() const;

	void setText(const std::string& text, const std::string& font);

	void draw() override;

private:
	SDL_Rect position;
	std::string text;
	std::string font;
	SDL_Color color;
	SDL_Texture* texture;




};
#endif
