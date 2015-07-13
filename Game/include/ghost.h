#ifndef GHOST_H
#define GHOST_H

#include "core/sprite.h"
#include "room.h"

using namespace std;

class Ghost : public Object
{
public:

	typedef enum { NONE, IDLE, RUNNING } State;
    typedef enum { MOVED, STOPPED } Event;
    typedef enum { LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3 } Direction;

    Ghost(Object *parent, ObjectID id, double x, double y, int mass, bool walkable, string type, int dir);
    ~Ghost();

    Direction direction();
    void get_playerx(int pos_x);
    void get_playery(int pos_y);
    void set_direction(Direction direction);
    void update_vision();
    void walk();
    void update_direction(unsigned long elapsed);
    void change_animation(string path);

    double damage();

private:
    string type;
    int player_posx;
    int player_posy;
    double m_damage;

    void draw_self();
    void update_self(unsigned long elapsed);
    unique_ptr<Animation> m_animation;
    Direction m_direction;
    unsigned long m_last = 0;
};


#endif