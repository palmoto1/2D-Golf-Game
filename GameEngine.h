#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include "Component.h" 
#include "GameState.h"


class Collider;
class GameManager;
class AssetManager;
class Vector;

constexpr int MAX_LEVEL = 5;
constexpr int MAX_STROKES = 10;


class GameEngine
{
public:
	static GameEngine* getInstance();
	

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static GameManager* gameManager;
	static AssetManager* assetManager;
	

	void initialize(const char* title, const std::string& resPath, int x, int y, int w, int h, bool fullscreen);

	void run();

	void handleEvents();
	void render();
	void update();
	void clean();

	void loadLevel();
	void loadMapEntities();
	void loadScoreBoard();

	void handleCollisions();
	void clearLevel();
	void checkStrokes();
	void checkGameStatus();

	void addScore(int strikes);

	void resetGame();

	~GameEngine();

protected:
	GameEngine();

private:

	static bool running;


	SDL_Window* win = nullptr;

	GameState::State state;

	std::string resPath;

	Uint32 frameStart = 0u;
	int frameTime = 0;

	int score = 0;
	int strokes = 0;


};



#endif

