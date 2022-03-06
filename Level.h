#ifndef LEVEL_H
#define LEVEL_H

#include "Vector.h"
#include "TileMap.h"
#include <vector>

/*keeps level data*/

class Level{

public:

	Vector getPlayerPos() const {
		return playerPos;
	}
	Vector getHolePos() const {
		return holePos;
	}

	void setPlayerPos(const Vector& v) {
		playerPos = v;
	}
	void setHolePos(const Vector& v) {
		holePos = v;
	}

	TileMap* getLevelMap() {
		return levelMap;
	}

	void setLevelMap(TileMap* map) {
		levelMap = map;
	}

	int getNumber() const {
		return number;
	}

	void increaseNumber() {
		number++;
	}

	void resetNumber() {
		number = 0;
	}



	void clean() {
		delete levelMap;
	}

private:
	Vector playerPos;
	Vector holePos;
	TileMap* levelMap = nullptr;
	int number = 0;


};

#endif;
