#include "boss.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

#include <core/animation.h>

#include <iostream>

using namespace std;

Boss::Boss(Object *parent, ObjectID id, double x, double y, int mass, bool walkable, int dir)
    : Object(parent, id, x, y), m_damage(0.9), m_animation (new Animation("res/sprites/boss_running.png",
    	0, 0, 90, 90, 6, 120, true)), m_direction((Direction) dir), m_last(0)
{
    this->set_mass(mass);
    this->set_w(70);
    this->set_h(70);
    this->set_walkable(walkable);
    this->set_summoned(false);
    this->set_created(false);
    update_vision();
}

Boss::~Boss()
{
}

Boss::Direction
Boss::direction()
{
    return m_direction;
}

void
Boss::update_vision()
{
}

void
Boss::set_direction(Direction direction)
{
    m_direction = direction;
}

void
Boss::draw_self()
{
    m_animation->draw(x(), y());
}

void
Boss::walk()
{
    double speed = 1.3;
    if(player_posx < this->x())
        set_x(x() - speed);
    else
        set_x(x() + speed);

    if(player_posy < this->y())
        set_y(y() - speed);
    else
        set_y(y() + speed);

    if(player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy < this->y())
        set_direction(Boss::UP);
    else if(player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy > this->y())
        set_direction(Boss::DOWN);
    else if(player_posx < this->x())
        set_direction(Boss::LEFT);
    else
        set_direction(Boss::RIGHT);
}

void
Boss::update_direction(unsigned long elapsed)
{
    m_animation->set_row(this->direction());
}

void
Boss::get_playerx(int pos_x)
{
    player_posx = pos_x;
}

void
Boss::get_playery(int pos_y)
{
    player_posy = pos_y;
}

double
Boss::damage()
{
    return m_damage;
}

void
Boss::update_self(unsigned long elapsed)
{

    set_x(this->x());
    set_y(this->y());
   
    update_direction(elapsed);
    m_animation->update(elapsed);
    walk();
}
void
Boss::set_position(double x, double y)
{
    set_x(x);
    set_y(y);
}

void
Boss::set_summoned(bool t)
{
    m_summoned = t;
}

void
Boss::set_created(bool t)
{
    m_created = t;
}