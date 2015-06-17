#ifndef ROOM_H
#define ROOM_H


#include <core/object.h>
#include <list>

#include "item.h"

using std::list;

class Guard;

class Room: public Object
{
public:
	Room(Object *parent, ObjectID id, string type = "None");

	Room *r_left;
	Room *r_right;
	Room *r_top;
	Room *r_botton;

	string type;
	int pos_x;
	int pos_y;

	void check_entry();
	string room_type();

	list <Object *> items;

	void add_list(Object *);
	const list<Object *>& get_items();
	void remove_item(Object *);

private:
	Guard *m_guard;

	void draw_id(Room *,Room *, int, int);
	void draw_self();
	void draw_items(string, string, int, int, int, int, bool);

    void update_self(unsigned long);

    void add_door(char direction, int x, int y);
    void randomize_items();

    bool m_doors;
};

#endif
