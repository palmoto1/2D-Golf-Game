#ifndef ENTITYGROUPS_H
#define ENTITYGROUPS_H

/*stores enum for different types of entity groups*/

struct EntityGroup {

	enum EntityGroups : int
	{
		TILE_GROUP,
		WALL_GROUP,
		WATER_GROUP,
		MOVING_OBJECT_GROUP,
		NON_MOVING_OBJECT_GROUP,
		UI_GROUP
	};
};


#endif 

