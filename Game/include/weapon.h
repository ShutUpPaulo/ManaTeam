#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "item.h"

using namespace std;

class Weapon : public Image
{
public:
    Weapon(Object *parent, ObjectID id, const string& path, int resistance,
     double damage, int attack_speed);

    double m_damage;
    int m_attack_speed;
    int m_resistance;
};

#endif