
#include <iostream>
#include <core/image.h>
#include <core/keyboardevent.h>
#include <core/environment.h>

#include "item.h"

Item::Item(Object *parent, ObjectID id, const string& path, double x, double y, bool walkable)
    : Image(parent, path)
{
    set_position(x, y);
    set_walkable(walkable);
}
