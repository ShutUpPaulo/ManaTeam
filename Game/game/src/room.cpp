#include "room.h"
#include "item.h"
#include <string>
#include <core/font.h>
#include <core/environment.h>

Room::Room(Object *parent, ObjectID id)
: Object(parent, id), m_left(nullptr), m_right(nullptr), m_top(nullptr), m_botton(nullptr)
{
	Item *piso = new Item(this,"piso",0,0,true);
	piso->change_sprite("res/tile_sheets/tile1.png");
	piso->set_x(0);
	piso->set_y(0);
	piso->set_w(120);
	piso->set_h(120);
	add_child(piso);
}

void Room::draw_self()
{
	Environment *env = Environment::get_instance();
	shared_ptr <Font> font = env->resources_manager->get_font("res/fonts/TakaoExGothic.ttf");
	env->canvas->set_font(font);
	env->canvas->draw(id(),300,400,Color::RED);
}

