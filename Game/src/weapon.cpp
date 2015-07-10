#include <iostream>
#include <core/image.h>
#include <core/keyboardevent.h>
#include <core/environment.h>

#include "weapon.h"

Weapon::Weapon(Object *parent, ObjectID id, const string& path, 
	double x, double y, double mass, bool walkable, int resistance,
	double damage, int attack_speed, string type)
    : Item(parent, id, path, x, y, mass, walkable)
{
	
}
