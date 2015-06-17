#include <iostream>
#include <core/animation.h>
#include <core/environment.h>

#include "sight.h"

Sight::Sight(Object *parent, ObjectID id, double x, double y, double w, double h)
    : Object(parent, id, x, y, w, h)
{
}

Sight::~Sight()
{
}

//Alterar
void
Sight::draw_self()
{
	Environment *env = Environment::get_instance();
	Rect rect {x(),y(),w(),h()};
	env->canvas->draw(rect, Color::WHITE);

}

void
Sight::update_self()
{
    set_x(this->x());
    set_y(this->y());
}
