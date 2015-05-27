#ifndef ITEM_H
#define ITEM_H

#include <core/object.h>
#include <core/keyboardeventlistener.h>
#include <string>

using namespace std;

class Item : public Object
{
public:
    Item(Object *parent, ObjectID id, double posx, double posy, bool walk, string type = "none");
    ~Item();
    
	void change_sprite(string);

	string type;
    bool walkable;
private:
	string current_sprite;

    void draw_self();
    void update_self();
};

#endif
