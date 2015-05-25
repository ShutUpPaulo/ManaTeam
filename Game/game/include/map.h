#ifndef MAP_H
#define MAP_H


#include <core/object.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <utility>

#include "room.h"

using std::pair;
using std::vector;

#define MAX 25

class Map: public Object
{
public:
	Map();

    enum Position {LEFT = 1, RIGHT = 2, TOP = 3, BOTTOM = 4};
	Room * current_room;
private:

    bool matriz[50][50];
	void CreateRoom(Room *, int*, int, int, int);
	void draw_self();

public:
	Room * room();
	void enter_room(Room *, Room *);
	void GenerateMap(int);
	
};
#endif
