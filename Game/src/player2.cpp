/*
 * Implementação da classe Player2.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "player2.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

ActionID Player2::hitExitDoorID { "hitExitDoorID()" };

using std::make_pair;

class Player2::Impl
{
public:
    Impl(Player2 *player2, Map * current_map)
        : m_player2(player2), m_direction(Player2::LEFT),
        m_moviment(make_pair(0.0, 0.0)), current_map(current_map)
    {
    }

    Direction direction() const { return m_direction; }
    void set_direction(Direction direction) { m_direction = direction; }

    const pair<double, double>& moviment() const { return m_moviment; }

    void set_moviment(double xaxis, double yaxis)
    {
        m_moviment = make_pair(xaxis, yaxis);
    }

    void enter_room(Room * anterior, Room * nova, int posx, int posy)
    {
        m_player2->set_x(posx);
        m_player2->set_y(posy);
        current_map->enter_room(anterior, nova);
        
    }

private:
    Player2 *m_player2;
    Direction m_direction;
    pair<double, double> m_moviment;
    Map * current_map;
};

class Idle : public SpriteState
{
public:
    Idle(Player2 *player2)
        : m_player2(player2), m_animation(new Animation("res/sprites/idle.png",
            0, 0, 41, 81, 1, 500, true)), m_left(0), m_right(0), m_top(0), m_down(0)
    {
    }

    ~Idle() {}

    void enter(int)
    {
        m_player2->set_dimensions(m_animation->w(), m_animation->h());
        m_right = m_left = m_down = m_top = 0;
    }

    void leave(int)
    {
    }

    bool on_event(const KeyboardEvent& event)
    {
        switch (event.state())
        {
        case KeyboardEvent::PRESSED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 1;
                return true;

            case KeyboardEvent::UP:
                m_top = 1;
                return true;

            case KeyboardEvent::DOWN:
                m_down = 1;
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 0;
                return true;

            case KeyboardEvent::UP:
                m_top = 0;
                return true;

            case KeyboardEvent::DOWN:
                m_down = 0;
                return true;

            default:
                break;
            }
            break;
        }

        return false;
    }

    void draw()
    {
        m_animation->draw(m_player2->x(), m_player2->y());
    }

    void update(unsigned long elapsed)
    {
       

        if (m_left)
        {
            m_player2->set_moviment(-1.0, 0.0);
            m_player2->set_direction(Player2::LEFT);
            m_player2->report_event(Player2::MOVED);
        } else if (m_right)
        {
            m_player2->set_moviment(0.0, 0.0);
            m_player2->set_direction(Player2::RIGHT);
            m_player2->report_event(Player2::MOVED);
        }
        if (m_top)
        {
            m_player2->set_moviment(0.0, -1.0);
            m_player2->set_direction(Player2::UP);
            m_player2->report_event(Player2::MOVED);
        }else if (m_down)
        {
            m_player2->set_moviment(0.0, 1.0);
            m_player2->set_direction(Player2::DOWN);
            m_player2->report_event(Player2::MOVED);
        }

        Player2::Direction dir = m_player2->direction();
        int row = dir;
        m_animation->set_row(row);
        m_animation->update(elapsed);
    }

private:
    Player2 *m_player2;
    unique_ptr<Animation> m_animation;
    int m_left, m_right, m_top, m_down;
};

class Running : public SpriteState
{
public:
    Running(Player2 *player2, Map * current_map)
        : m_player2(player2), m_animation(
        new Animation("res/sprites/running.png", 0, 0, 60, 60, 8, 60, true)),
        m_left(0), m_right(0), m_top(0), m_down(0), m_last(0), current_map(current_map)
    {
    }

    ~Running() {}

    const double speed = 350.0;

    void enter(int from)
    {
        m_player2->set_dimensions(m_animation->w(), m_animation->h());

        Player2::Direction dir = m_player2->direction();

        m_right = dir == Player2::RIGHT ? 1 : 0;
        m_left = dir == Player2::LEFT ? 1 : 0;
        m_top = dir == Player2::UP ? 1 : 0;
        m_down = dir == Player2::DOWN ? 1 : 0;
        m_last = 0;

        if (from == Player2::IDLE)
        {
            auto moviment = m_player2->moviment();
            double x = moviment.first * speed;
            double y = moviment.second * speed;
            m_player2->set_moviment(x, y);
        }
    }

    void leave(int)
    {
    }

    void draw()
    {
        m_animation->draw(m_player2->x(), m_player2->y());
    }

    bool on_event(const KeyboardEvent& event)
    {
        switch (event.state())
        {
        case KeyboardEvent::PRESSED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 1;
                return true;

            case KeyboardEvent::UP:
                m_top = 1;
                return true;

            case KeyboardEvent::DOWN:
                m_down = 1;
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 0;
                return true;

            case KeyboardEvent::UP:
                m_top = 0;
                return true;

            case KeyboardEvent::DOWN:
                m_down = 0;
                return true;

            default:
                break;
            }
            break;
        }

        return false;
    }

    void enter_room(Room * anterior, Room * nova, int posx, int posy)
    {
        m_player2->set_x(posx);
        m_player2->set_y(posy);
        current_map->enter_room(anterior, nova);
        
    }

    void update(unsigned long elapsed)
    {

        if (m_left)
        {
            m_player2->set_direction(Player2::LEFT);
            m_player2->report_event(Player2::MOVED);
        }else if (m_right)
        {
            m_player2->set_direction(Player2::RIGHT);
            m_player2->report_event(Player2::MOVED);
        }
        if (m_top)
        {
            m_player2->set_direction(Player2::UP);
            m_player2->report_event(Player2::MOVED);
        } else if (m_down)
        {
            m_player2->set_direction(Player2::DOWN);
            m_player2->report_event(Player2::MOVED);
        }

        if(!m_top && !m_down && !m_right && !m_left)
        {
            m_player2->report_event(Player2::STOPPED);
        }
        else
        {
            m_player2->set_moviment(speed*(m_right - m_left), speed*(m_down - m_top));
        }

        

        Player2::Direction dir = m_player2->direction();
        int row = dir;
        m_animation->set_row(row);

        if (not m_last)
        {
            m_last = elapsed;
        }

        auto moviment = m_player2->moviment();
        unsigned long delta = elapsed - m_last;
        double x = m_player2->x() + (moviment.first * delta)/1000.0;
        double y = m_player2->y() + (moviment.second * delta)/1000.0;

        /*limite da sala */
        Environment *env = Environment::get_instance();

        if (x + m_player2->w() > env->canvas->w())
        {
            x = env->canvas->w() - m_player2->w();
        }

        if ((x >= env->canvas->w() - m_player2->w() and moviment.first > 0) or 
            (x <= 0 and moviment.first < 0))
        {
            x -= (moviment.first * delta)/1000.0;
        }

        if (y + m_player2->h() > env->canvas->h())
        {
            y = env->canvas->h() - m_player2->h();
        }

        if ((y >= env->canvas->h() - m_player2->h() and moviment.second > 0) or 
            (y <= 0 and moviment.second < 0))
        {
            y -= (moviment.second * delta)/1000.0;
        }

        m_player2->set_x(x);
        m_player2->set_y(y);

        m_last = elapsed;
        m_animation->update(elapsed);

        int posx,posy;
        posx = (int) x;
        posy = (int) y;

        if(posx <= 5 && ( posy >= 280 && posy <= 420) && current_map->current_room->r_left)
        {

            enter_room(current_map->current_room, current_map->current_room->r_left, 1120, posy);
        }
        else if(posx >= 1200 && ( posy >= 280 && posy <= 420) && current_map->current_room->r_right)
        {

            enter_room(current_map->current_room, current_map->current_room->r_right, 80, posy);
        }
        else if(posy <= 5  && ( posx >= 600 && posx <= 680) && current_map->current_room->r_top)
        {

            enter_room(current_map->current_room, current_map->current_room->r_top, posx, 580);
        }
        else if(posy >= 620  && ( posx >= 600 && posx <= 680) && current_map->current_room->r_botton)
        {

            enter_room(current_map->current_room, current_map->current_room->r_botton, posx, 80);
        }


        /*Colisoes com os itens */
        vector <Item*> aux = current_map->current_room->items;

        for(int i = 0; i < aux.size(); i++)
        {
            if(aux[i]->type == "key")
            {
                if (((posx + 30 > aux[i]->x()) && (posx + 30 < (aux[i]->x() + 32))) && ((posy + 30> aux[i]->y()) && (posy + 30 < (aux[i]->y() + 32))))
                {
                    current_map->current_room->remove_child(aux[i]);
                    cout << "peguei a porra da chave" << endl;
                    //pick_key();
                } 
            }
            else if(aux[i]->type == "finaldoor")
            {
                //if(has_key())
                //{
                    if (((posx + 40 > aux[i]->x()) && (posx + 40 < (aux[i]->x() + 80))) && ((posy + 40> aux[i]->y()) && (posy + 40 < (aux[i]->y() + 80))))
                    {
//                        cout << "você ganhou o jogo!" << endl;
                        //drop_key();

                        m_player2->notify(Player2::hitExitDoorID, "stage2");
                        //Passa pro prox level
                        //Level *next_level = new Level("stage","stage2");
                        //next_level->set_next("stage2");
                    } 
                //}
            }
        }

    }

private:
    Player2 *m_player2;
    unique_ptr<Animation> m_animation;
    short m_left, m_right, m_top, m_down;
    unsigned long m_last;
    Map * current_map;
};

Player2::Player2(Object *parent, const string& id, Map * current_map)
    : Sprite(parent, id), current_map(current_map), m_impl(new Player2::Impl(this, current_map))
{
    add_state(IDLE, new Idle(this));
    add_state(RUNNING, new Running(this, current_map));

    add_transition(MOVED, IDLE, RUNNING);
    add_transition(STOPPED, RUNNING, IDLE);
    change_state(IDLE, NONE);

    Environment *env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

Player2::~Player2()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_listener(this);
}

Player2::Direction
Player2::direction() const
{
    return m_impl->direction();
}

void
Player2::set_direction(Direction direction)
{
    m_impl->set_direction(direction);
}

const pair<double, double>&
Player2::moviment() const
{
    return m_impl->moviment();
}

void
Player2::set_moviment(double xaxis, double yaxis)
{
    m_impl->set_moviment(xaxis, yaxis);
}

void
Player2::enter_room(Room * anterior, Room * nova, int posx, int posy)
{
    m_impl->enter_room(anterior, nova, posx, posy);
}
