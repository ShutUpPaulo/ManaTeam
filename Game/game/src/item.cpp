#include "item.h"
#include <core/animation.h>
#include <core/keyboardevent.h>
#include <core/environment.h>

Item::Item(Object *parent, ObjectID id, double posx, double posy, Map::Priority priority, bool walk)
    : Object(parent, id)
{

    walkable = walk;
    
    set_x(posx);
    set_y(posy);
}

Item::~Item()
{
}

//Alterar
void
Item::draw_self()
{
    //const Color color { 80, 180, 205 };
    Animation* item;
    
    item = new Animation("res/tile_sheets/map1.png", 0, 0, 1200, 720, 1,0, false);
    item->draw(x(),y());
    //Environment *env = Environment::get_instance();
    //env->canvas->fill(bounding_box(), color);
}

void
Item::update_self(unsigned long elapsed)
{
    set_x(this->x());
    set_y(this->y());
}
