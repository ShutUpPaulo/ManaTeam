#ifndef ROOM_H
#define ROOM_H

#include <core/object.h>
#include <core/rect.h>
#include <list>

#include "item.h"

#define INFINITE 99999.9

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

    bool m_doors;
    Rect center_area;

	void draw_id(Room *,Room *, int, int);
	void draw_items(string, string, int, int, int, int, bool);

    void update_self(unsigned long);

    void add_door(char direction, int x, int y);
    void pre_drawing(const string item_name, string item_type, int percentage, 
    	int pos_x, int pos_y, int width, int height, bool walkable);

    void fill_floor(const string& name);
    void add_corners(const string& name);
    void add_guard(const string& name);
    void add_itens();

    bool place(Object *object, double x, double y);
};

#endif
