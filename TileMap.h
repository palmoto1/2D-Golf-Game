#ifndef TILEMAP_H
#define TILEMAP_H
#include <string>

/*represents a map based on a number of tiles*/

class TileMap
{
public:
	
	TileMap(int scale, int tSize);


	void loadMap(const std::string& path, int width, int height );
	void addTile(int x, int y, int color_id);


	~TileMap();

private:

	int mapScale = 0;
	int tileSize = 0;
	int width = 0;
	int height = 0;
	


};
#endif

