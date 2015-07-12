#include "guard.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

#include <iostream>

ActionID Guard::removeGuardID { "removeGuardID()" };

using namespace std;

Guard::Guard(Object *parent, ObjectID id, double x, double y, int mass, bool walkable, string t, int dir)

    : Object(parent, id, x, y), m_type(t), m_damage(0.7), m_life(100), m_animation (new Animation("res/sprites/guarda1_running.png",
    	0, 0, 70, 70, 8, 120, true)), m_direction((Direction) dir), m_last(0)
{
    this->set_mass(mass);
    this->set_w(70);
    this->set_h(70);
    this->set_walkable(walkable);
    update_vision();

    if(m_type == "hard")
    {
        change_animation("res/sprites/guarda3_running.png");
    }
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
    double speed = 0.6;
    if(m_type == "easy")
        return;
    else if(m_type == "normal" || m_type == "hard")
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
    else if(m_type == "follow")
    {

        if(player_posx + 70 < this->x())
            set_x(x() - speed);
        else if(player_posx > this->x() + 70)
            set_x(x() + speed);

        if(player_posy + 70 < this->y())
            set_y(y() - speed);
        else if(player_posy > this->y() + 70)
            set_y(y() + speed);

        if(player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy < this->y())
            set_direction(Guard::UP);
        else if(player_posx > this->x() - 100 && player_posx < this->x() + 100 && player_posy > this->y())
            set_direction(Guard::DOWN);
        else if(player_posx < this->x())
            set_direction(Guard::LEFT);
        else
            set_direction(Guard::RIGHT);

    }
        return;
}

void
Guard::update_direction(unsigned long elapsed)
{

    if(m_type == "easy")
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
    else if (m_type == "normal")
    {
        if(elapsed - m_last > 5000)
        {
            int test = ((int)direction() + 2) % 4;
            Direction new_direction = (Direction)test;
            set_direction(new_direction);

            m_last = elapsed;
        }
    }
    else if(m_type == "hard" || m_type == "follow")
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
Guard::get_playerx(int pos_x)
{
    player_posx = pos_x;
}

void
Guard::get_playery(int pos_y)
{
    player_posy = pos_y;
}

double
Guard::damage()
{
    return m_damage;
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

void
Guard::change_animation(string path)
{
    m_animation.reset(new Animation(path, 0, 0, 70, 70, 8, 120, true));
}

double
Guard::life()
{
    return m_life;
}
string 
Guard::type()
{
    return m_type;
}

void
Guard::set_type(string t)
{
    m_type = t;
}

void
Guard::receive_dmg(double dmg)
{
    m_life = m_life - dmg;
    if(m_life < 0)
        m_life = 0;
    //cout << "Guarda apanhou " << dmg << " de dano, vida atual: " << m_life << endl;
}
