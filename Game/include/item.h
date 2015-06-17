#ifndef ITEM_H
#define ITEM_H

#include <core/object.h>
#include <string>

using namespace std;

class Item : public Object
{
public:
    Item(Object *parent, ObjectID id, double x, double y, double w, double h, bool walkable);
    ~Item();
    
	void change_sprite(string);
private:
	string current_sprite;

    void draw_self();
    void update_self();
};

#endif
