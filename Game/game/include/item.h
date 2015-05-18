#ifndef ITEM_H
#define ITEM_H

#include "map.h"

#include <object.h>
#include <keyboardeventlistener.h>

class Item : public Object
{
public:
    Item(Object *parent, ObjectID id, double posx, double posy, Map::Priority priority, bool walk);
    ~Item();
    
    bool walkable;

private:
    void draw_self();
    void update_self(unsigned long elapsed);
};

#endif
