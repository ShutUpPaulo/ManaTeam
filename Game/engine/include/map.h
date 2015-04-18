#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include <iostream>
#include <ctime>

#define MAX 25

class Map
{
public:
	typedef struct Room_
	{
		int id;
        bool hasMap;
		struct Room_ * left;
		struct Room_ * right;
		struct Room_ * top;
		struct Room_ * bot;
	}room;

    bool matriz[5][5];
	
	enum Position {LEFT = 1, RIGHT = 2, TOP = 3, BOTTOM = 4};
	
private:
	room *InsertRoom(int, room*, room*, room*, room*);
	void CreateRoom(room *, int*, int, int);
	
public:
	void ResetMap(room *);
	room * GenerateMap();
	
};
#endif
