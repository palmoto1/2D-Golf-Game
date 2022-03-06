
#include "Gameengine.h"
#include <SDL.h>
#include <string>


/*write path to where assets folder is located*/
std::string resPath = "c:/";

int main(int argc, char* argv[]) {
	GameEngine* g = GameEngine::getInstance();
	g->initialize("Test", resPath, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);
	g->run();
	

	return 0;
}