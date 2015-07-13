#ifndef GUARD_H
#define GUARD_H

#include "core/sprite.h"
#include "room.h"
#include "sight.h"

using namespace std;

class Guard : public Object
{
public:

    typedef enum { NONE, IDLE, RUNNING } State;
    typedef enum { MOVED, STOPPED } Event;
    typedef enum { LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3 } Direction;

    Guard(Object *parent, ObjectID id, double x, double y, int mass, bool walkable, string type, int dir);
    ~Guard();

    static ActionID removeGuardID;
    static ActionID walkID;
    

    Direction direction();
    void get_playerx(int pos_x);
    void get_playery(int pos_y);
    void set_direction(Direction direction);
    void update_vision();
    void walk(unsigned long elapsed);
    void update_direction(unsigned long elapsed);
    void change_animation(string path);
    
    string type();
    string old_type();
    void set_type(string t);
    void set_old_type(string t);

    double health();
    double damage();
    void receive_dmg(double dmg);
    string m_old_type;

private:
    string m_type;

    int player_posx;
    int player_posy;
    double m_damage;
    double m_health;

    void draw_self();
    void update_self(unsigned long elapsed);
    unique_ptr<Animation> m_animation;
    Direction m_direction;
    unsigned long m_last;
};


#endif