#include "ghost.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

#include <core/animation.h>

#include <iostream>

using namespace std;

Ghost::Ghost(Object *parent, ObjectID id, double x, double y, int mass, bool walkable, string t, int dir)
    : Object(parent, id, x, y), type(t), m_damage(0.05), m_animation (new Animation("res/sprites/ghost_guarda1_running.png",
    	0, 0, 70, 70, 8, 60, true)), m_direction((Direction) dir), m_last(0)
{

    if(t == "hard")
        m_animation.reset(new Animation("res/sprites/ghost_guarda3_running.png", 0, 0, 70, 70, 8, 120, true));

    cout << id << endl;
    this->set_mass(mass);
    this->set_w(70);
    this->set_h(70);
    this->set_walkable(walkable);
    update_vision();
}

Ghost::~Ghost()
{
}

Ghost::Direction
Ghost::direction()
{
    return m_direction;
}

void
Ghost::update_vision()
{
}

void
Ghost::set_direction(Direction direction)
{
    m_direction = direction;
}

void
Ghost::draw_self()
{
    m_animation->draw(x(), y());
}

void
Ghost::walk()
{
    double speed = 0.3;
    if(player_posx < this->x())
        set_x(x() - speed);
    else
        set_x(x() + speed);

    if(player_posy < this->y())
        set_y(y() - speed);
    else
        set_y(y() + speed);

    if(player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy < this->y())
        set_direction(Ghost::UP);
    else if(player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy > this->y())
        set_direction(Ghost::DOWN);
    else if(player_posx < this->x())
        set_direction(Ghost::LEFT);
    else
        set_direction(Ghost::RIGHT);
}

void
Ghost::update_direction(unsigned long elapsed)
{
    if(elapsed - m_last > 5000)
    {
        int random = rand()%100;

        if(random < 25)
            set_direction(Ghost::LEFT);
        else if(random < 50)
            set_direction(Ghost::UP);
        else if(random < 75)
            set_direction(Ghost::RIGHT);
        else
            set_direction(Ghost::DOWN);

        m_last = elapsed;
    }
    m_animation->set_row(this->direction());
}

void
Ghost::get_playerx(int pos_x)
{
    player_posx = pos_x;
}

void
Ghost::get_playery(int pos_y)
{
    player_posy = pos_y;
}

double
Ghost::damage()
{
    return m_damage;
}

void
Ghost::update_self(unsigned long elapsed)
{

    set_x(this->x());
    set_y(this->y());
   
    update_direction(elapsed);
    m_animation->update(elapsed);
    walk();
}