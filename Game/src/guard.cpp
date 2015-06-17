#include "guard.h"

#include "core/level.h"
#include "core/environment.h"
#include "core/keyboardevent.h"

Guard::Guard(Object *parent, ObjectID id, double x, double y)
    : Object(parent, id, x, y), m_animation (new Animation("res/sprites/idle.png",
    	0, 0, 70, 70, 2, 1000, true))
{
}

Guard::~Guard()
{
}

void 
Guard::draw()
{
	m_animation->draw(this->x(), this->y());	
}

//Alterar
void
Guard::draw_self()
{
    //const Color color { 80, 180, 205 };

    m_animation->draw(x(), y());
    //Environment *env = Environment::get_instance();
    //env->canvas->fill(bounding_box(), color);
}

void
Guard::update(unsigned long elapsed)
{
    set_x(this->x());
    set_y(this->y());
    //m_animation->set_row(rand()%4);
    m_animation->update(elapsed);
}

    