#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#define MAX 15

class Map
{
private:
	typedef struct Room_
	{
		int id;
		struct Room_ * left;
		struct Room_ * right;
		struct Room_ * top;
		struct Room_ * bot;
	}room;
	
	enum Position {LEFT = 1, RIGHT = 2, TOP = 3, BOTTOM = 4};
	
private:
	room *InsertRoom(int, room*, room*, room*, room*);
	void CreateRoom(room *, int);
	
public:
	void ResetMap(room *);
	void GenerateMap();
	
};
#endif
