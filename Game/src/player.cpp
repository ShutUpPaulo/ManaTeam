/*
 * Implementação da classe Player.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "player.h"
#include "core/rect.h"
#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

ActionID Player::hitExitDoorID { "hitExitDoorID()" };
ActionID Player::jumpNextLevelID { "jumpNextLevelID()" };
ActionID Player::takeItemID { "takeItemID()" };
ActionID Player::openDoorID { "openDoorID()" };
ActionID Player::pushItemID { "pushItemID()" };
ActionID Player::repeatLevelID { "repeatLevelID()" };

using std::make_pair;

class Player::Impl
{
public:
    Impl(Player *player, Map *current_map, bool key)
        : m_sanity_loss(0), m_player(player), m_direction(Player::LEFT),
        m_moviment(make_pair(0.0, 0.0)), m_current_map(current_map), 
        m_key(key), m_strength(0.0), m_life(100.0), m_sanity(100.0), m_stamina(100.0),
        m_pill(false), m_weapon(false), m_secondary(false)
    {
    }

    int m_sanity_loss;
    Direction direction() const { return m_direction; }
    void set_direction(Direction direction) { m_direction = direction; }

    const pair<double, double>& moviment() const { return m_moviment; }

    void set_moviment(double xaxis, double yaxis)
    {
        m_moviment = make_pair(xaxis, yaxis);
    }

    void set_current(Room *nova, int posx, int posy)
    {
        m_player->set_x(posx);
        m_player->set_y(posy);
        m_current_map->set_current(nova);
    }

    void set_strength(double strength)
    {
        m_strength = strength;
    }

    double strength()
    {
        return m_strength;
    }

    void set_life(double life)
    {
        m_life = life;
    }

    double life()
    {
        return m_life;
    }

    void set_sanity(double sanity)
    {
        m_sanity = sanity;
    }

    double sanity()
    {
        return m_sanity;
    }
    double stamina()
    {
        return m_stamina;
    }

    void set_stamina(double stamina)
    {
        m_stamina = stamina;
    }

    void get_pill()
    {
        if(m_pill == true)
            return;

        Environment *env = Environment::get_instance();

        m_pill = true;

        Item* pill = new Item(m_player, "icon_pill", "res/items/thumb.pill.png", (double)env->canvas->w() * 1/35 + 2, (double)env->canvas->h() * 25/30 + 2, 9999, true);
        m_player->add_child(pill);
    }

    void get_key()
    {
        if(m_key == true)
            return;

        Environment *env = Environment::get_instance();
        double size = env->canvas->w()/35;

        m_key = true;

        Item* key = new Item(m_player, "icon_key", "res/items/thumb.key.png", (double)env->canvas->w() * 1/35 + size + 2, (double)env->canvas->h() * 25/30 + size + 2, 9999, true);
        m_player->add_child(key);
    }
    void set_key(bool input)
    {
        m_key = input;
    }
    bool has_key()
    {
        return m_key;
    }
    void show_life()
    {
        Environment *env = Environment::get_instance();
        Rect healthbar {(double)env->canvas->w()/15, (double)env->canvas->h()/24, m_player->life()*2, 12};
        env->canvas->fill(healthbar, Color::RED);
        Rect borda {(double)env->canvas->w()/15, (double)env->canvas->h()/24, 100*2, 12};
        env->canvas->draw(borda, Color::RED);
    }
    void show_sanity()
    {
        Environment *env = Environment::get_instance();
        Rect sanitybar {(double)env->canvas->w()/15, (double)env->canvas->h()/17, m_player->sanity()*2, 12};
        env->canvas->fill(sanitybar, Color::GREEN);
        Rect borda {(double)env->canvas->w()/15, (double)env->canvas->h()/17, 100*2, 12};
        env->canvas->draw(borda, Color::GREEN);
    }
    void show_stamina()
    {
        Environment *env = Environment::get_instance();
        double stamina = m_player->stamina()*2;

        if(stamina < 0)
            stamina = 0;

        Rect staminabar {(double)env->canvas->w()/15, (double)env->canvas->h()/13, stamina, 12};
        env->canvas->fill(staminabar, Color::YELLOW);
        Rect borda {(double)env->canvas->w()/15, (double)env->canvas->h()/13, 100*2, 12};
        env->canvas->draw(borda, Color::YELLOW);
    }

    void show_inventory()
    {
        Environment *env = Environment::get_instance();
        double size = env->canvas->w()/35;

        Rect item1 {(double)(env->canvas->w() * 1/35), (double)env->canvas->h() * 25/30, size, size};
        Rect item2 {(double)env->canvas->w() * 1/35 + size, (double)env->canvas->h() * 25/30 - size, size, size};
        Rect item3 {(double)env->canvas->w() * 1/35 + 2*size, (double)env->canvas->h() * 25/30, size, size};
        Rect item4 {(double)env->canvas->w() * 1/35 + size, (double)env->canvas->h() * 25/30 + size, size, size};
        Rect not_item {(double)env->canvas->w() * 1/35 + size, (double)env->canvas->h() * 25/30, size, size};
        env->canvas->draw(item1, Color::WHITE);
        env->canvas->draw(item2, Color::WHITE);
        env->canvas->draw(item3, Color::WHITE);
        env->canvas->draw(item4, Color::WHITE);
        env->canvas->fill(not_item, Color::WHITE);
    }


    void use_pill()
    {
        if(m_pill)
        {
            double recover = 35;
            m_player->set_life(m_player->life() + recover);
            if(m_player->life() > 100)
                m_player->set_life(100);

            cout << "Pegou uma pilula! Recuperou " << recover << " de vida." << endl;
            
            const list<Object *> items = m_player->children();
            for (auto item : items)
            {
                if(item->id() == "icon_pill")
                {
                    m_pill = false;
                    m_player->remove_child(item);
                }
            }
        }  
    }

    void take_item()
    {
        m_player->notify(takeItemID, "take_item");
    }
    void jump_level()
    {
        m_player->notify(jumpNextLevelID, "next_level");
    }
    void open_door()
    {
        m_player->notify(openDoorID, "open_door");
    }
    void push_item()
    {
        m_player->notify(pushItemID, "push_item");
    }
    void you_died()
    {
        m_player->notify(repeatLevelID, "you_died");
    }

private:
    Player *m_player;
    Direction m_direction;
    pair<double, double> m_moviment;
    Map *m_current_map;
    bool m_key;
    double m_strength;
    double m_life;
    double m_sanity;
    double m_stamina;
    bool m_pill;
    bool m_weapon;
    bool m_secondary;
};

class Idle : public SpriteState
{
public:
    Idle(Player *player)
        : m_player(player), m_animation(new Animation("res/sprites/idle.png",
            0, 0, 70, 70, 2, 1000, true)), m_left(0), m_right(0), m_top(0), 
        m_down(0), m_running(false)
    {
    }

    ~Idle() {}

    void enter(int)
    {
        m_player->set_dimensions(m_animation->w(), m_animation->h());
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
            case KeyboardEvent::A:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
            case KeyboardEvent::D:
                m_right = 1;
                return true;

            case KeyboardEvent::UP:
            case KeyboardEvent::W:
                m_top = 1;
                return true;

            case KeyboardEvent::DOWN:
            case KeyboardEvent::S:
                m_down = 1;
                return true;

            case KeyboardEvent::LSHIFT:
                m_running = true;
                return true;

            case KeyboardEvent::Q:
                m_player->use_pill();
                return true;

            case KeyboardEvent::E:
                m_player->open_door();
                return true;

            case KeyboardEvent::K:
                m_player->take_item();
                return true;

            case KeyboardEvent::U:
                m_player->report_event(Player::DUCKING);
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
            case KeyboardEvent::A:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
            case KeyboardEvent::D:
                m_right = 0;
                return true;

            case KeyboardEvent::UP:
            case KeyboardEvent::W:
                m_top = 0;
                return true;

            case KeyboardEvent::DOWN:
            case KeyboardEvent::S:
                m_down = 0;
                return true;

            case KeyboardEvent::LSHIFT:
                m_running = false;
                return true;

            case KeyboardEvent::P:
                m_player->jump_level();
                return true;

            case KeyboardEvent::K:
                m_player->take_item();
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
        m_animation->draw(m_player->x(), m_player->y());
        m_player->show_life();
        m_player->show_sanity();
        m_player->show_inventory();
        m_player->show_stamina();
    }

    void update(unsigned long elapsed)
    {
        if(m_player->life() < 1)
            m_player->you_died();

        if(m_player->stamina() < 100)
        {
            m_player->set_stamina(m_player->stamina() + 0.05);
            if(m_player->stamina() > 100)
                m_player->set_stamina(100);
        }


        if(! m_player->m_sanity_loss)
            m_player->m_sanity_loss = elapsed;

        if(elapsed - m_player->m_sanity_loss > 3000)
        {
            m_player->set_sanity(m_player->sanity() - 1);
            if(m_player->sanity() < 0)
                m_player->set_sanity(0);
            m_player->m_sanity_loss = elapsed;
        }
        if (m_left)
        {
            m_player->set_moviment(-1.0, 0.0);
            m_player->set_direction(Player::LEFT);
            m_player->report_event(Player::MOVED);
        } else if (m_right)
        {
            m_player->set_moviment(0.0, 0.0);
            m_player->set_direction(Player::RIGHT);
            m_player->report_event(Player::MOVED);
        }
        if (m_top)
        {
            m_player->set_moviment(0.0, -1.0);
            m_player->set_direction(Player::UP);
            m_player->report_event(Player::MOVED);
        }else if (m_down)
        {
            m_player->set_moviment(0.0, 1.0);
            m_player->set_direction(Player::DOWN);
            m_player->report_event(Player::MOVED);
        }

        Player::Direction dir = m_player->direction();
        int row = dir;
        m_animation->set_row(row);
        m_animation->update(elapsed);
    }

private:
    Player *m_player;
    unique_ptr<Animation> m_animation;
    int m_left, m_right, m_top, m_down;
    bool m_running;
};

class Running : public SpriteState
{
public:
    Running(Player *player, Map * current_map, bool key)
        : m_player(player), m_animation(
        new Animation("res/sprites/running.png", 0, 0, 70, 70, 8, 60, true)),
        m_left(0), m_right(0), m_top(0), m_down(0), m_last(0), 
        current_map(current_map), m_key(key), m_running(false), m_pushing(false)
    {
    }

    ~Running() {}

    const double m_speed = 250.0;

    void enter(int from)
    {
        m_player->set_dimensions(m_animation->w(), m_animation->h());

        Player::Direction dir = m_player->direction();

        m_right = dir == Player::RIGHT ? 1 : 0;
        m_left = dir == Player::LEFT ? 1 : 0;
        m_top = dir == Player::UP ? 1 : 0;
        m_down = dir == Player::DOWN ? 1 : 0;
        m_last = 0;
        m_running = 0;

        if (from == Player::IDLE)
        {
            auto moviment = m_player->moviment();
            double x = moviment.first * m_speed;
            double y = moviment.second * m_speed;
            m_player->set_moviment(x, y);
        }
    }

    void leave(int)
    {
    }

    void draw()
    {
        m_animation->draw(m_player->x(), m_player->y());
        m_player->show_life();
        m_player->show_sanity();
        m_player->show_inventory();
        m_player->show_stamina();
    }

    bool on_event(const KeyboardEvent& event)
    {
        switch (event.state())
        {
        case KeyboardEvent::PRESSED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
            case KeyboardEvent::A:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
            case KeyboardEvent::D:
                m_right = 1;
                return true;

            case KeyboardEvent::UP:
            case KeyboardEvent::W:
                m_top = 1;
                return true;

            case KeyboardEvent::DOWN:
            case KeyboardEvent::S:
                m_down = 1;
                return true;

            case KeyboardEvent::LSHIFT:
                m_running = true;
                return true;

            case KeyboardEvent::Q:
                m_player->use_pill();
                return true;

            case KeyboardEvent::K:
                m_player->take_item();
                m_pushing = true;
                return true;

            case KeyboardEvent::E:
                m_player->open_door();
                return true;

            case KeyboardEvent::U:
                m_player->report_event(Player::DUCKING);
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
            case KeyboardEvent::A:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
            case KeyboardEvent::D:
                m_right = 0;
                return true;

            case KeyboardEvent::UP:
            case KeyboardEvent::W:
                m_top = 0;
                return true;

            case KeyboardEvent::DOWN:
            case KeyboardEvent::S:
                m_down = 0;
                return true;

            case KeyboardEvent::LSHIFT:
                m_running = false;
                return true;

            case KeyboardEvent::K:
                m_pushing = false;
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
        double speed = m_speed;

        if(m_player->life() < 1)
            m_player->you_died();

        if(m_player->stamina() < 100)
        {
            m_player->set_stamina(m_player->stamina() + 0.05);
            if(m_player->stamina() > 100)
                m_player->set_stamina(100);
        }
        
        if(m_running)
        {
            if(m_player->stamina() > 1)
            {

                speed += 50 + 10 * ((int)m_player->stamina())/5;
                m_player->set_stamina(m_player->stamina() - 0.25);
                if(m_player->stamina() < 1)
                    m_player->set_stamina(-(0.05 * 1000));
            }

//            cout << "speed: " << speed << endl;
        }

        if(m_pushing)
        {
            m_player->push_item();
        }

        if(! m_player->m_sanity_loss)
            m_player->m_sanity_loss = elapsed;

        if(elapsed - m_player->m_sanity_loss > 3000)
        {
            m_player->set_sanity(m_player->sanity() - 1);
            if(m_player->sanity() < 0)
                m_player->set_sanity(0);
            m_player->m_sanity_loss = elapsed;
        }

        if (m_left)
        {
            m_player->set_direction(Player::LEFT);
            m_player->report_event(Player::MOVED);
        }else if (m_right)
        {
            m_player->set_direction(Player::RIGHT);
            m_player->report_event(Player::MOVED);
        }
        if (m_top)
        {
            m_player->set_direction(Player::UP);
            m_player->report_event(Player::MOVED);
        } else if (m_down)
        {
            m_player->set_direction(Player::DOWN);
            m_player->report_event(Player::MOVED);
        }

        if(!m_top && !m_down && !m_right && !m_left)
        {
            m_player->report_event(Player::STOPPED);
        }
        else
        {
            m_player->set_moviment(speed*(m_right - m_left), speed*(m_down - m_top));
        }

        

        Player::Direction dir = m_player->direction();
        int row = dir;
        m_animation->set_row(row);

        if (not m_last)
        {
            m_last = elapsed;
        }

        auto moviment = m_player->moviment();
        unsigned long delta = elapsed - m_last;
        double x = m_player->x() + (moviment.first * delta)/1000.0;
        double y = m_player->y() + (moviment.second * delta)/1000.0;

        /*limite da sala */
        Environment *env = Environment::get_instance();

        if (x + m_player->w() > env->canvas->w())
        {
            x = env->canvas->w() - m_player->w();
        }

        if ((x >= env->canvas->w() - m_player->w() and moviment.first > 0) or 
            (x <= 0 and moviment.first < 0))
        {
            x -= (moviment.first * delta)/1000.0;
        }

        if (y + m_player->h() > env->canvas->h())
        {
            y = env->canvas->h() - m_player->h();
        }

        if ((y >= env->canvas->h() - m_player->h() and moviment.second > 0) or 
            (y <= 0 and moviment.second < 0))
        {
            y -= (moviment.second * delta)/1000.0;
        }

        m_player->set_x(x);
        m_player->set_y(y);

        m_last = elapsed;
        m_animation->update(elapsed);

    }

private:
    Player *m_player;
    unique_ptr<Animation> m_animation;
    short m_left, m_right, m_top, m_down;
    unsigned long m_last;
    Map * current_map;
    bool m_key, m_running, m_pushing;
};

class Duck : public SpriteState
{
public:
    Duck(Player *player)
        : m_player(player), m_animation(new Animation("res/sprites/duck.png",
            0, 0, 70, 70, 2, 1000, true)), m_left(0), m_right(0), m_top(0), 
        m_down(0)
    {
    }

    ~Duck() {}

    void enter(int)
    {
        m_player->set_dimensions(m_animation->w(), m_animation->h());
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
            case KeyboardEvent::A:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
            case KeyboardEvent::D:
                m_right = 1;
                return true;

            case KeyboardEvent::UP:
            case KeyboardEvent::W:
                m_top = 1;
                return true;

            case KeyboardEvent::DOWN:
            case KeyboardEvent::S:
                m_down = 1;
                return true;

            case KeyboardEvent::Q:
                m_player->use_pill();
                return true;

            case KeyboardEvent::E:
                m_player->open_door();
                return true;

            case KeyboardEvent::K:
                m_player->take_item();
                return true;

            case KeyboardEvent::U:
                m_player->report_event(Player::STANDING);
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
            case KeyboardEvent::A:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
            case KeyboardEvent::D:
                m_right = 0;
                return true;

            case KeyboardEvent::UP:
            case KeyboardEvent::W:
                m_top = 0;
                return true;

            case KeyboardEvent::DOWN:
            case KeyboardEvent::S:
                m_down = 0;
                return true;

            case KeyboardEvent::P:
                m_player->jump_level();
                return true;

            case KeyboardEvent::K:
                m_player->take_item();
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
        m_animation->draw(m_player->x(), m_player->y());
        m_player->show_life();
        m_player->show_sanity();
        m_player->show_inventory();
        m_player->show_stamina();
    }

    void update(unsigned long elapsed)
    {
        if(m_player->life() < 1)
            m_player->you_died();

        if(m_player->stamina() < 100)
        {
            m_player->set_stamina(m_player->stamina() + 0.05);
            if(m_player->stamina() > 100)
                m_player->set_stamina(100);
        }


        if(! m_player->m_sanity_loss)
            m_player->m_sanity_loss = elapsed;

        if(elapsed - m_player->m_sanity_loss > 3000)
        {
            m_player->set_sanity(m_player->sanity() - 1);
            if(m_player->sanity() < 0)
                m_player->set_sanity(0);
            m_player->m_sanity_loss = elapsed;
        }

        if (m_left)
        {
            m_player->set_moviment(-1.0, 0.0);
            m_player->set_direction(Player::LEFT);
        } else if (m_right)
        {
            m_player->set_moviment(0.0, 0.0);
            m_player->set_direction(Player::RIGHT);
        }
        if (m_top)
        {
            m_player->set_moviment(0.0, -1.0);
            m_player->set_direction(Player::UP);
        }else if (m_down)
        {
            m_player->set_moviment(0.0, 1.0);
            m_player->set_direction(Player::DOWN);
        }

        Player::Direction dir = m_player->direction();
        int row = dir;
        m_animation->set_row(row);
        m_animation->update(elapsed);
    }

private:
    Player *m_player;
    unique_ptr<Animation> m_animation;
    int m_left, m_right, m_top, m_down;
};

Player::Player(Object *parent, const string& id, Map *current_map)
    : Sprite(parent, id), m_sanity_loss(0), m_impl(new Player::Impl(this, current_map, m_key)),
     m_key(false), m_pill(false), m_weapon(false), m_secondary(false)
{
    add_state(IDLE, new Idle(this));
    add_state(RUNNING, new Running(this, current_map, m_key));
    add_state(DUCK, new Duck(this));

    add_transition(MOVED, IDLE, RUNNING);
    add_transition(STOPPED, RUNNING, IDLE);
    add_transition(DUCKING, IDLE, DUCK);
    add_transition(STANDING, DUCK, IDLE);
    add_transition(DUCKING, RUNNING, DUCK);
    add_transition(STANDING, DUCK, RUNNING);
    change_state(IDLE, NONE);

    Environment *env = Environment::get_instance();
    env->events_manager->register_listener(this);
}

Player::~Player()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_listener(this);
}

Player::Direction
Player::direction() const
{
    return m_impl->direction();
}

void
Player::set_direction(Direction direction)
{
    m_impl->set_direction(direction);
}

const pair<double, double>&
Player::moviment() const
{
    return m_impl->moviment();
}

void
Player::set_moviment(double xaxis, double yaxis)
{
    m_impl->set_moviment(xaxis, yaxis);
}

void
Player::set_current(Room * nova, int posx, int posy)
{
    m_impl->set_current(nova, posx, posy);
}

void
Player::set_strength(double strength)
{
    m_impl->set_strength(strength);
}

void
Player::set_life(double life)
{
    m_impl->set_life(life);
}

void
Player::set_sanity(double sanity)
{
    m_impl->set_sanity(sanity);
}

void
Player::set_stamina(double stamina)
{
    m_impl->set_stamina(stamina);
}

double
Player::strength()
{
    return m_impl->strength();
}

double
Player::life()
{
    return m_impl->life();
}

double
Player::sanity()
{
    return m_impl->sanity();
}

double
Player::stamina()
{
    return m_impl->stamina();
}

void
Player::get_key()
{
    m_impl->get_key();
}

void
Player::set_key(bool input)
{
    m_impl->set_key(input);
}

bool
Player::has_key()
{
    return m_impl->has_key();
}

void
Player::show_life()
{
     m_impl->show_life();
}
void
Player::show_sanity()
{
    m_impl->show_sanity();
}
void
Player::show_inventory()
{
    m_impl->show_inventory();
}
void
Player::show_stamina()
{
    m_impl->show_stamina();
}

void
Player::take_item()
{
    m_impl->take_item();
}

void
Player::jump_level()
{
    m_impl->jump_level();
}

void
Player::open_door()
{
    m_impl->open_door();
}

void
Player::push_item()
{
    m_impl->push_item();
}

void
Player::use_pill()
{
    m_impl->use_pill();
}

void
Player::get_pill()
{
    m_impl->get_pill();
}
void 
Player::you_died()
{
    m_impl->you_died();
}
