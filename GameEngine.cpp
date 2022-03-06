#include "Gameengine.h"
#include "TextureManager.h"
#include "TileMap.h"
#include "Transform.h"
#include "Sprite.h"
#include "Vector.h"
#include "BallController.h"
#include "Collider.h" 
#include "GameManager.h"
#include "AssetManager.h"
#include "Level.h"
#include "Label.h"
#include "EntityGroups.h"
#include "EntityManager.h"
#include "Entity.h"
#include <cstring>



using namespace std;

const size_t FPS = 60u;
const size_t frameDelay = 1000u / FPS;


EntityManager entityManager;
Level level;

Entity* player = nullptr;
Entity* hole = nullptr;
Entity* scoreLabel = nullptr;
Entity* strokesLabel = nullptr;
Entity* gameLabel = nullptr;


std::vector<Entity*>& tiles = entityManager.getEntityGroup(EntityGroup::TILE_GROUP);
std::vector<Entity*>& barriers = entityManager.getEntityGroup(EntityGroup::WALL_GROUP);
std::vector<Entity*>& waters = entityManager.getEntityGroup(EntityGroup::WATER_GROUP);
std::vector<Entity*>& labels = entityManager.getEntityGroup(EntityGroup::UI_GROUP);


SDL_Renderer* GameEngine::renderer;
SDL_Event GameEngine::event;
GameManager* GameEngine::gameManager;
AssetManager* GameEngine::assetManager;


bool GameEngine::running = false;


GameEngine::GameEngine() {

}

GameEngine* GameEngine::getInstance(){
return new GameEngine;
}


void GameEngine::initialize(const char* title, const std::string& resPath, int x, int y, int w, int h, bool fullscreen)
{


	int win_flag = 0;
	if (fullscreen)
		win_flag = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cerr << SDL_GetError() << endl;
		return;
	}

	win = SDL_CreateWindow(title, x, y, w, h, win_flag);
	if (!win)
	{
		cerr << SDL_GetError() << endl;
		return;
	}

	renderer = SDL_CreateRenderer(win, -1, 0);
	if (!renderer)
	{
		cerr << SDL_GetError() << endl;
		return;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	running = true;

	state = GameState::IDLE;

	this->resPath = resPath;

	gameManager = new GameManager(&entityManager);
	assetManager = new AssetManager();

	if (TTF_Init() == -1) {
		cout << "UI system failed" << endl;
	}


	//adding fonts and textures
	assetManager->addFont("size64", (resPath + "resourses/fonts/lunchds.ttf").c_str(), 64);
	assetManager->addFont("size32", (resPath + "resourses/fonts/lunchds.ttf").c_str(), 32);

	assetManager->addTexture("ball", (resPath + "resourses/images/ball_twini.png").c_str(), true, 255, 255, 255);
	assetManager->addTexture("hole", (resPath + "resourses/images/hole_small.png").c_str(), true, 255, 255, 255);

	assetManager->addTexture("grass", (resPath + "resourses/images/grass_real.png").c_str(), false, 0, 0, 0);
	assetManager->addTexture("wall", (resPath + "resourses/images/wall_real.png").c_str(), false, 0, 0, 0);
	assetManager->addTexture("water", (resPath + "resourses/images/water_real.png").c_str(), false, 0, 0, 0);


	//creating map and setting initial player position
	level.setLevelMap(new TileMap(1, 32));
	level.setPlayerPos(Vector(390.0f, 560.0f));

	//loading level and and game objects
	loadLevel();
	loadMapEntities();


	//loading initial game label
	gameLabel = gameManager->createLabel("size64","Press mouse to start!", 30, 200, { 255, 255, 255 });

	


}


void GameEngine::handleEvents() {
	
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		if (state == GameState::IDLE) {
			gameLabel->inactivate();
			state = GameState::READY;
			break;
		}
		if (state == GameState::READY) {
			player->getComponent<BallController>().setAble(true);
			loadScoreBoard();
			state = GameState::ACTIVE;
		}
		if (state == GameState::ACTIVE) {
			++strokes;
			strokesLabel->getComponent<Label>().setText("Strokes: " + std::to_string(strokes), "size32");
		}
	case SDL_MOUSEBUTTONUP:
		break;
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				running = false;
			default:
				break;
			}
	default:
		break;
	}
}



void GameEngine::loadMapEntities() {
	player = gameManager->createBall("ball", level.getPlayerPos(), Vector(0.0f, 0.0f), 0.95f, 0.0f, true, 16, 16, 1);
	hole = gameManager->createStaticObject("hole", level.getHolePos(), 16, 16, 1);
}

void GameEngine::loadScoreBoard() {
	scoreLabel = gameManager->createLabel("size32", "Score: 0", 10, 10, { 255, 255, 255 });
	strokesLabel = gameManager->createLabel("size32", "Strokes: 0", 610, 10, { 255, 255, 255 });
}


//score system based on how many strikes the player have when they hit the goal
void GameEngine::addScore(int strikes) {
	switch (strikes) {
	case 1: 
		score += 100;
		break;
	case 2:
		score += 80;
		break;
	case 3:
		score += 60;
		break;
	case 4:
		score += 40;
		break;
	case 5:
		score += 20;
		break;
	default:
		score += 10;
		break;
	}
}

 
void GameEngine::update()
{
	
		entityManager.filter();
		entityManager.update();	
		handleCollisions();
		checkStrokes();
		checkGameStatus();
		
	
		
	}






void GameEngine::render() {
	SDL_RenderClear(renderer);
	entityManager.draw();
	SDL_RenderPresent(renderer);
}




void GameEngine::run() {


	while (running) {

		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	clean();
}

void GameEngine::loadLevel()
{

	level.increaseNumber();
	

	if (level.getLevelMap() != nullptr) {

		switch (level.getNumber()) {
		case 1:
			level.getLevelMap()->loadMap((resPath + "resourses/maps/level1.txt").c_str(), 25, 20);
			level.setHolePos(Vector(390.0f, 50.0f));
			break;
		case 2:
			level.getLevelMap()->loadMap((resPath + "resourses/maps/level2.txt").c_str(), 25, 20);
			level.setHolePos(Vector(390.0f, 50.0f));
			scoreLabel->getComponent<Label>().setText("Score: " + std::to_string(score), "size32");
			
			break;
		case 3:
			level.getLevelMap()->loadMap((resPath + "resourses/maps/level3.txt").c_str(), 25, 20);
			level.setHolePos(Vector(550.0f, 50.0f));
			scoreLabel->getComponent<Label>().setText("Score: " + std::to_string(score), "size32");
			break;
		case 4:
			level.getLevelMap()->loadMap((resPath + "resourses/maps/level4.txt").c_str(), 25, 20);
			level.setHolePos(Vector(100.0f, 50.0f));
			scoreLabel->getComponent<Label>().setText("Score: " + std::to_string(score), "size32");
			break;
		case 5:
			level.getLevelMap()->loadMap((resPath + "resourses/maps/level5.txt").c_str(), 25, 20);
			level.setHolePos(Vector(200, 50.0f));
			scoreLabel->getComponent<Label>().setText("Score: " + std::to_string(score), "size32");
			break;
		case 6:
			level.getLevelMap()->loadMap((resPath + "resourses/maps/empty_map.txt").c_str(), 25, 20);
			state = GameState::WIN;

			break;
		default:
			break;
		}
	}


}

void GameEngine::clearLevel()
{
	for (auto& t : tiles) {
		t->inactivate();
	}

	for (auto& t : barriers) {
		t->inactivate();
	}
	for (auto& t : waters) {
		t->inactivate();
	}
}


void GameEngine::handleCollisions()
{	

	player->getComponent<Ball>().checkMapBoundryCollision(800 - 40, 25, 640 - 40, 25);

	int wallHits = 0;
	for (auto& c : barriers)
		player->getComponent<Ball>().checkWallCollsion(c->getComponent<Collider>().getCollider(), wallHits);
	

	for (auto& w : waters) {
		if (player->getComponent<Ball>().hasCollision(w->getComponent<Collider>().getCollider())) {
			state = GameState::LOST;
		}
	}


	//the ball cant get in the hole if it travels to fast
	if (player->getComponent<Ball>().getAcceleration() < 10.0f) {

		Collider& holeCollider = hole->getComponent<Collider>();

		if (player->getComponent<Ball>().hasCollision(holeCollider.getCollider())) {
			
			addScore(strokes);
			strokes = 0;
			strokesLabel->getComponent<Label>().setText("Strokes: " + std::to_string(strokes), "size32");

			clearLevel();
			loadLevel();

			player->getComponent<Transform>().setPosition(level.getPlayerPos());
			player->getComponent<Ball>().reset();
			hole->getComponent<Transform>().setPosition(level.getHolePos());
		}
	}
}



void GameEngine::checkStrokes() {
	if (strokes > MAX_STROKES && player->getComponent<Ball>().getAcceleration() == 0.0f) {
		state = GameState::LOST;
	}
}

void GameEngine::resetGame(){
	state = GameState::IDLE;

	strokesLabel->inactivate();
	scoreLabel->inactivate();

	strokes = 0;
	score = 0;

	level.resetNumber();
	clearLevel();
	loadLevel();

	player->getComponent<BallController>().setAble(false);
	player->getComponent<Transform>().setPosition(level.getPlayerPos());
	player->getComponent<Ball>().reset();

	hole->getComponent<Transform>().setPosition(level.getHolePos());
}



void GameEngine::checkGameStatus(){
	if (state == GameState::LOST) {
		gameLabel = gameManager->createLabel("size64", "YOU LOST!", 250, 200, { 255, 255, 255 });
		resetGame();
	}
	if (state == GameState::WIN) {
		gameLabel = gameManager->createLabel("size64", "YOU WON! Score: " + std::to_string(score), 100, 200, { 255, 255, 255 });
		resetGame();
	}
}





void GameEngine::clean() {

	
	delete gameManager;
	delete assetManager;
	level.clean();
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}



GameEngine::~GameEngine() {
}