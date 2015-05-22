#include "room.h"
#include "item.h"
#include <string>
#include <iostream>
#include <core/font.h>
#include <core/environment.h>

Room::Room(Object *parent, ObjectID id)
: Object(parent, id), m_left(nullptr), m_right(nullptr), m_top(nullptr), m_botton(nullptr)
{
	Item *piso;
	string id_piso = "piso";
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			id_piso += '1';
			piso = new Item(this,id_piso,i*60,j*60,true);
			piso->change_sprite("res/tile_sheets/tile2.png");
			piso->set_w(60);
			piso->set_h(60);
			piso->set_position(i*60,j*60);
			add_child(piso);
		}
	}
}

void Room::draw_self()
{
	Environment *env = Environment::get_instance();
	shared_ptr <Font> font = env->resources_manager->get_font("res/fonts/TakaoExGothic.ttf");
	env->canvas->set_font(font);
	env->canvas->draw(id(),300,400,Color::RED);
}

