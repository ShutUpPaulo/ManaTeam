#include "guard.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

#include <iostream>

using namespace std;

Guard::Guard(Object *parent, ObjectID id, double x, double y, int mass, bool walkable)
    : Object(parent, id, x, y), m_animation (new Animation("res/sprites/idle.png",
    	0, 0, 70, 70, 2, 1000, true)), m_direction(Guard::RIGHT), m_last(0)
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
Guard::update_self(unsigned long elapsed)
{
    if(elapsed - m_last > 3000)
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
        update_vision();
    }

    m_animation->set_row(this->direction());
    set_x(this->x());
    set_y(this->y());
    //m_animation->set_row(rand()%4);
    m_animation->update(elapsed);
}

    