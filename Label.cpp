#include "Label.h"
#include "AssetManager.h"
#include "GameEngine.h"


Label::Label(int xPos, int yPos, const std::string& t, const std::string& f, const SDL_Color& c) :
	text(t), font(f), color(c)

{
	position.x = xPos;
	position.y = yPos;
	setText(text, font);

}

Label::~Label() {
	SDL_DestroyTexture(texture);
}

std::string Label::getText() const
{
	return text;
}

void Label::setText(const std::string& text, const std::string& font) {

	SDL_DestroyTexture(texture);
	SDL_Surface* surface =
		TTF_RenderText_Blended(GameEngine::assetManager->getFont(font), text.c_str(), color);

	texture = SDL_CreateTextureFromSurface(GameEngine::renderer, surface);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);


}

void Label::draw()
{
	SDL_RenderCopy(GameEngine::renderer, texture, NULL, &position);
}