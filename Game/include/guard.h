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
    typedef enum { LEFT, UP, RIGHT, DOWN } Direction;

    Guard(Object *parent, ObjectID id, double x, double y, bool walkable);
    ~Guard();

    Direction direction();
    void set_direction(Direction direction);
    void update_vision();

private:
    void draw_self();
    void update_self(unsigned long elapsed);
    unique_ptr<Animation> m_animation;
    Direction m_direction;
    unsigned long m_last;

};


#endif