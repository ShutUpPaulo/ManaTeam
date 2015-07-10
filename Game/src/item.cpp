#include <iostream>
#include <core/image.h>
#include <core/keyboardevent.h>
#include <core/environment.h>

#include "item.h"

Item::Item(Object *parent, ObjectID id, const string& path, double x,
 double y, double mass, bool walkable)
    : Image(parent, id, path)
{
    set_position(x, y);
    set_walkable(walkable);
    set_mass(mass);
}
