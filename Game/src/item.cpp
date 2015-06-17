
#include <iostream>
#include <core/animation.h>
#include <core/keyboardevent.h>
#include <core/environment.h>

#include "item.h"

Item::Item(Object *parent, ObjectID id, double x, double y, double w, double h, bool walkable)
    : Object(parent, id, x, y, w, h)
{
    this->set_walkable(walkable);
}

Item::~Item()
{
}

//Alterar
void
Item::draw_self()
{
    Animation* item;
    
    item = new Animation(current_sprite, 0, 0, w(), h(), 1,0, false);
    
    item->draw(x(), y());
}

void
Item::change_sprite(string item)
{
    current_sprite = item;
}

void
Item::update_self()
{
    set_x(this->x());
    set_y(this->y());
}
