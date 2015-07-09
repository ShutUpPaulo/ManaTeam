#include "guard.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

#include <iostream>

using namespace std;

Guard::Guard(Object *parent, ObjectID id, double x, double y, int mass, bool walkable, string t, int dir)
    : Object(parent, id, x, y), m_animation (new Animation("res/sprites/idle.png",
    	0, 0, 70, 70, 2, 1000, true)), m_direction((Direction) dir), m_last(0), type(t)
{
    this->set_w(70);
    this->set_h(70);
    this->set_walkable(walkable);
    update_vision();
}

Guard::~Guard()
{
}

Guard::Direction
Guard::direction()
{
    return m_direction;
}

void
Guard::update_vision()
{
    const list<Object *> filhos = this->children();

    for (auto filho : filhos)
    {
        if(filho->id() == "visao")
        {
            remove_child(filho);
        }
    }

    if(direction() == Guard::RIGHT)
    {
        Sight *visao = new Sight(this, "visao", this->x()+40, this->y(), 200, 80);
        add_child(visao);
    }
    else if(direction() == Guard::LEFT)
    {
        Sight *visao = new Sight(this, "visao", this->x() - 200, this->y(), 240, 80);
        add_child(visao);
    }
    else if(direction() == Guard::UP)
    {
        Sight *visao = new Sight(this, "visao", this->x(), this->y() - 200, 80, 240);
        add_child(visao);
    }
    else if(direction() == Guard::DOWN)
    {
        Sight *visao = new Sight(this, "visao", this->x(), this->y() + 40, 80, 200);
        add_child(visao);
    }

}

void
Guard::set_direction(Direction direction)
{
    m_direction = direction;
}

void
Guard::draw_self()
{
    m_animation->draw(x(), y());
}

void
Guard::walk(unsigned long elapsed)
{
    if(type == "easy")
        return;
    else if(type == "normal" || type == "hard")
    {
        unsigned speed = 1;

        if(elapsed - m_last > 3000)
        {
            if(direction() == Guard::RIGHT || direction() == Guard::LEFT)
            {
                set_x(x() - speed + (speed * direction()));
            }
            if(direction() == Guard::UP || direction() == Guard::DOWN)
            {
                set_y(y() - 2 * speed + (speed * direction()));
            }
        }
    }
    else if(type == "hard")
        return;
}

void
Guard::update_direction(unsigned long elapsed)
{

    if(type == "easy")
    {
        if(elapsed - m_last > 1000)
        {
            int random = rand()%100;

            if(random < 25)
                set_direction(Guard::LEFT);
            else if(random < 50)
                set_direction(Guard::UP);
            else if(random < 75)
                set_direction(Guard::RIGHT);
            else
                set_direction(Guard::DOWN);

            m_last = elapsed;
        }
    }
    else if (type == "normal")
    {
        if(elapsed - m_last > 5000)
        {
            int test = ((int)direction() + 2) % 4;
            Direction new_direction = (Direction)test;
            set_direction(new_direction);

            m_last = elapsed;
        }
    }
    else if(type == "hard")
    {
        if(elapsed - m_last > 5000)
        {
            int random = rand()%100;

            if(random < 25)
                set_direction(Guard::LEFT);
            else if(random < 50)
                set_direction(Guard::UP);
            else if(random < 75)
                set_direction(Guard::RIGHT);
            else
                set_direction(Guard::DOWN);

            m_last = elapsed;
        }
    }
    m_animation->set_row(this->direction());
}

void
Guard::update_self(unsigned long elapsed)
{

    set_x(this->x());
    set_y(this->y());
   
    update_direction(elapsed);
    m_animation->update(elapsed);
    walk(elapsed);
    update_vision();
}

    