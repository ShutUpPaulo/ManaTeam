#ifndef MAP_H
#define MAP_H


#include <object.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>
#include <utility>

using std::pair;
using std::vector;

#define MAX 25

class Map: public Object
{
public:
	Map();

    enum Position {LEFT = 1, RIGHT = 2, TOP = 3, BOTTOM = 4};
	enum Priority {MAP = 0, SCEN = 1 , ITEM = 2, CHAR = 5};
	
	typedef struct Room_
	{
		int id;
		bool hasMap;
		struct Room_ * left;
		struct Room_ * right;
		struct Room_ * top;
		struct Room_ * bot;
		vector<Object *> objects;
	}room;
	
private:
    bool matriz[5][5];
	room *InsertRoom(int, room*, room*, room*, room*);
	void CreateRoom(room *, int*, int, int);
	void draw_self();

	
public:
    void AddObject(room *, Object *,  Priority);
	void ResetMap(room *);
	room * GenerateMap();
	
};
#endif
