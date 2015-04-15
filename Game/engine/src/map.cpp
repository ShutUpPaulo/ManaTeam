#include "map.h"

using namespace std;

// Insert Room
Map::room * Map::InsertRoom(int id, room * left, room * top, room * right, room * bot)
{
	room * newRoom = (room*) malloc(sizeof(room*));
	newRoom->left = left;
	newRoom->right = right;
	newRoom->top = top;
	newRoom->bot = bot;
	newRoom->id = id;
	
	return newRoom;
}

// Room Criation
void Map::CreateRoom(room *rooms, int id)
{
	int randomVar;
	
	srand(time(0));
	
	randomVar = rand() % 4+1;
	
	switch(randomVar)
	{	
		case LEFT:
			if(rooms->left != NULL)
				CreateRoom(rooms->left, id);
			else
				rooms->left = InsertRoom(id, NULL, NULL, rooms, NULL);
			break;
			
		case RIGHT:
			if(rooms->right != NULL)
				CreateRoom(rooms->right, id);
			else
				rooms->right = InsertRoom(id, rooms, NULL, NULL, NULL);
			break;
		
		case TOP:
			if(rooms->top != NULL)
				CreateRoom(rooms->top, id);
			else
				rooms->top = InsertRoom(id, NULL, NULL, NULL, rooms);
			break;
		
		case BOTTOM:
			if(rooms->bot != NULL)
				CreateRoom(rooms->bot, id);
			else
				rooms->bot = InsertRoom(id, NULL, rooms, NULL, NULL);
			break;
	}
}

// Delete rooms
void Map::ResetMap(room *rooms)
{
	if(rooms->left != NULL)
		ResetMap(rooms->left);
	if(rooms->top != NULL)
		ResetMap(rooms->top);
	if(rooms->right != NULL)
		ResetMap(rooms->right);
	if(rooms->bot != NULL)
		ResetMap(rooms->bot);
		
	free(rooms);
}

// Generate all the map
void Map::GenerateMap()
{
	int id = 0;
	
	room *rooms = InsertRoom(id, NULL, NULL, NULL, NULL);
	
	for(id = 1;id <= MAX; id++)
	{	
		CreateRoom(rooms,id);
	}
}

