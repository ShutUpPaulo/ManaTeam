/*
 * Implementação da classe Player2.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "player2.h"

#include "core/environment.h"
#include "core/keyboardevent.h"

using std::make_pair;

class Player2::Impl
{
public:
    Impl(Player2 *player2)
        : m_player2(player2), m_direction(Player2::LEFT),
        m_moviment(make_pair(0.0, 0.0))
    {
    }

    Direction direction() const { return m_direction; }
    void set_direction(Direction direction) { m_direction = direction; }

    const pair<double, double>& moviment() const { return m_moviment; }

    void set_moviment(double xaxis, double yaxis)
    {
        m_moviment = make_pair(xaxis, yaxis);
    }

private:
    Player2 *m_player2;
    Direction m_direction;
    pair<double, double> m_moviment;
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
    Running(Player2 *player2)
        : m_player2(player2), m_animation(
        new Animation("res/sprites/running.png", 0, 0, 60, 60, 8, 60, true)),
        m_left(0), m_right(0), m_top(0), m_down(0), m_last(0)
    {
    }

    ~Running() {}

    const double speed = 300.0;

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

        if ((x == env->canvas->w() - m_player2->w() and moviment.first > 0) or 
            (x <= 0 and moviment.first < 0))
        {
            m_player2->report_event(Player2::STOPPED);
        }
        
        if (y < 0)
        {
            y = 0;
        }

        if (y + m_player2->h() > env->canvas->h())
        {
            y = env->canvas->h() - m_player2->h();
        }

        if ((y == env->canvas->h() - m_player2->h() and moviment.second > 0) or 
            (y == 0 and moviment.second < 0))
        {
            m_player2->report_event(Player2::STOPPED);
        }

        m_player2->set_x(x);
        m_player2->set_y(y);

        m_last = elapsed;
        m_animation->update(elapsed);
    }

private:
    Player2 *m_player2;
    unique_ptr<Animation> m_animation;
    short m_left, m_right, m_top, m_down;
    unsigned long m_last;
};

Player2::Player2(Object *parent, const string& id)
    : Sprite(parent, id), m_impl(new Player2::Impl(this))
{
    add_state(IDLE, new Idle(this));
    add_state(RUNNING, new Running(this));

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
