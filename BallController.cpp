#include "BallController.h"
#include "GameEngine.h"
#include "Entity.h"

void BallController::setAble(bool able)
{
	this->able = able;
}

void BallController::initialize() {
	ball = &this->getEntity()->getComponent<Ball>();
	able = false;
}


void BallController::update() {

	if (able)
		switch (GameEngine::event.type) {
		case SDL_MOUSEBUTTONDOWN:
			mouseDown = SDL_GetTicks();
			break;
		case SDL_MOUSEBUTTONUP:

			ball->setAim(static_cast<float>(GameEngine::event.button.x), static_cast<float>(GameEngine::event.button.y));
			mouseUp = SDL_GetTicks();
			ball->charge(static_cast<float>(mouseUp - mouseDown));
			ball->shoot();
			reset();
			break;

		default:
			break;
		}

}

void BallController::reset() {
	mouseDown = 0u;
	mouseUp = 0u;
}
