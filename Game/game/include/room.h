#ifndef ROOM_H
#define ROOM_H

#include <core/object.h>

class Room: public Object
{
public:
	Room(Object *parent, ObjectID id);

private:
	//bool hasMap;
	Room *m_left;
	Room *m_right;
	Room *m_top;
	Room *m_botton;

	void draw_self();
};

#endif