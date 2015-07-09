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

    Direction direction();
    void set_direction(Direction direction);
    void update_vision();
    void walk(unsigned long elapsed);
    void update_direction(unsigned long elapsed);

private:
    string type;

    void draw_self();
    void update_self(unsigned long elapsed);
    unique_ptr<Animation> m_animation;
    Direction m_direction;
    unsigned long m_last;
};


#endif