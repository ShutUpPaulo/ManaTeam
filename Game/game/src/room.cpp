#include "room.h"
#include "item.h"
#include <string>
#include <iostream>
#include <core/font.h>
#include <core/environment.h>
#include <core/rect.h>

Room::Room(Object *parent, ObjectID id)
: Object(parent, id), r_left(nullptr), r_right(nullptr), r_top(nullptr), r_botton(nullptr)
{
	Item *piso;
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			piso = new Item(this,"piso",i*60,j*60,true);
			piso->change_sprite("res/tile_sheets/tile1.png");
			piso->set_w(60);
			piso->set_h(60);
			piso->set_position(i*60,j*60);
			add_child(piso);
		}
	}
	

}

void Room::check_entry()
{
	Environment *env = Environment::get_instance();
	if(this->r_left)
	{
		Rect l_door {0, 340, 80, 80};
		env->canvas->draw(l_door, Color::WHITE);

	}
	if(this->r_top)
	{
		Rect t_door {600, 0, 80, 80};
		env->canvas->draw(t_door, Color::WHITE);

	}
	if(this->r_right)
	{
		Rect r_door {1200, 340, 80, 80};
		env->canvas->draw(r_door, Color::WHITE);

	}
	if(this->r_botton)
	{
		Rect b_door {600, 640, 80, 80};
		env->canvas->draw(b_door, Color::WHITE);

	}
}

void Room::draw_self()
{
	Environment *env = Environment::get_instance();
	shared_ptr <Font> font = env->resources_manager->get_font("res/fonts/TakaoExGothic.ttf");
	env->canvas->set_font(font);
	env->canvas->draw(id(),1150,20,Color::RED);

	if(this->r_left)
	{
		Rect l_door {0, 320, 80, 80};
		env->canvas->draw(l_door, Color::WHITE);

	}
	if(this->r_top)
	{
		Rect t_door {600, 0, 80, 80};
		env->canvas->draw(t_door, Color::WHITE);

	}
	if(this->r_right)
	{
		Rect r_door {1200, 320, 80, 80};
		env->canvas->draw(r_door, Color::WHITE);

	}
	if(this->r_botton)
	{
		Rect b_door {600, 640, 80, 80};
		env->canvas->draw(b_door, Color::WHITE);

	}

}

