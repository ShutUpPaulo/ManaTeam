#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "item.h"

using namespace std;

class Weapon : public Item
{
public:
    Weapon(Object *parent, ObjectID id, const string& path,
     double x, double y, double mass, bool walkable, int resistance,
     double damage, int attack_speed, string type);
};

#endif