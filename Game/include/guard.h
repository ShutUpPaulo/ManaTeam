#ifndef GUARD_H
#define GUARD_H

#include "core/sprite.h"
#include "room.h"

using namespace std;

class Guard : public Object
{
public:

	typedef enum { NONE, IDLE, RUNNING } State;
    typedef enum { MOVED, STOPPED } Event;
    typedef enum { LEFT, UP, RIGHT, DOWN } Direction;

    Guard(Object *parent, ObjectID id, double x, double y);
    ~Guard();

    Direction direction() const;
    void set_direction(Direction direction);

    //const pair<double, double>& moviment() const;
    //void set_moviment(double xaxis, double yaxis);

private:
	//class Impl;
    //unique_ptr<Impl> m_impl;
    void draw();
    void draw_self();
    void update(unsigned long elapsed);
    unique_ptr<Animation> m_animation;

};


#endif