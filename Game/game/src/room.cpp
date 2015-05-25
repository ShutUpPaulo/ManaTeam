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
	for(int i = 0; i < 22; i++)
	{
		for(int j = 0; j < 12; j++)
		{
			piso = new Item(this,"piso",i*60,j*60,true);
			piso->change_sprite("res/tile_sheets/tile1.png");
			piso->set_w(60);
			piso->set_h(60);
			add_child(piso);
		}
	}

	/*Adicionando cantos*/
	Item *canto = new Item(this,"canto", 0, 0,false);
	canto->change_sprite("res/tile_sheets/canto1.png");
	canto->set_w(80);
	canto->set_h(80);
	add_child(canto);

	canto = new Item(this,"canto", 1200, 0,false);
	canto->change_sprite("res/tile_sheets/canto2.png");
	canto->set_w(80);
	canto->set_h(80);
	add_child(canto);

	canto = new Item(this,"canto", 0, 640,false);
	canto->change_sprite("res/tile_sheets/canto4.png");
	canto->set_w(80);
	canto->set_h(80);
	add_child(canto);

	canto = new Item(this,"canto", 1200, 640,false);
	canto->change_sprite("res/tile_sheets/canto3.png");
	canto->set_w(80);
	canto->set_h(80);
	add_child(canto);

	/*Adicionando paredes */
	Item *parede;
	for(int x = 1; x < 15; x++)
	{
		parede = new Item(this, "parede", x*80, 0, false);
		parede->change_sprite("res/tile_sheets/parede2.png");
		parede->set_w(80);
		parede->set_h(80);
		add_child(parede);

		parede = new Item(this, "parede", x*80, 640, false);
		parede->change_sprite("res/tile_sheets/parede4.png");
		parede->set_w(80);
		parede->set_h(80);
		add_child(parede);
	}
	for(int y = 1; y < 8; y++ )
	{
		parede = new Item(this, "parede", 0, y*80, false);
		parede->change_sprite("res/tile_sheets/parede1.png");
		parede->set_w(80);
		parede->set_h(80);
		add_child(parede);

		parede = new Item(this, "parede", 1200, y*80, false);
		parede->change_sprite("res/tile_sheets/parede3.png");
		parede->set_w(80);
		parede->set_h(80);
		add_child(parede);
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

void
Room::draw_id(Room * anterior, Room * sala, int x, int y)
{

	Environment *env = Environment::get_instance();
	shared_ptr <Font> font = env->resources_manager->get_font("res/fonts/TakaoExGothic.ttf");
	env->canvas->set_font(font);
	env->canvas->draw(sala->id(),x,y,Color::RED);

	if(sala->r_left && sala->r_left != anterior)
	{
		env->canvas->draw("-", x - 20, y,Color::RED);
		draw_id(sala, sala->r_left, x - 100, y);
	}
	if(sala->r_top && sala->r_top != anterior)
	{
		env->canvas->draw("|", x + 20, y - 30,Color::RED);
		draw_id(sala, sala->r_top, x, y - 60);
	}
	if(sala->r_right && sala->r_right != anterior)
	{
		env->canvas->draw("-", x + 80, y,Color::RED);
		draw_id(sala, sala->r_right, x + 100, y);
	}
	if(sala->r_botton && sala->r_botton != anterior)
	{
		env->canvas->draw("|", x + 20, y + 25,Color::RED);
		draw_id(sala, sala->r_botton, x, y + 60);
	}
}

void Room::draw_self()
{
	Environment *env = Environment::get_instance();
	draw_id(NULL, this, 640, 360);
	Rect square {635, 355, 80, 40};
	env->canvas->draw(square, Color::RED);

	Item *porta;

	if(this->r_left)
	{
		Rect l_door {0, 320, 80, 80};
		env->canvas->draw(l_door, Color::WHITE);

		/*Adicionando portas */
		porta = new Item(this,"porta", 0, 320, true);
		porta->change_sprite("res/tile_sheets/porta1.png");
		porta->set_w(80);
		porta->set_h(80);
		add_child(porta);

	}
	if(this->r_top)
	{
		Rect t_door {600, 0, 80, 80};
		env->canvas->draw(t_door, Color::WHITE);

		porta = new Item(this,"porta", 600, 0, true);
		porta->change_sprite("res/tile_sheets/porta2.png");
		porta->set_w(80);
		porta->set_h(80);
		add_child(porta);

	}
	if(this->r_right)
	{
		Rect r_door {1200, 320, 80, 80};
		env->canvas->draw(r_door, Color::WHITE);

		porta = new Item(this,"porta", 1200, 320, true);
		porta->change_sprite("res/tile_sheets/porta3.png");
		porta->set_w(80);
		porta->set_h(80);
		add_child(porta);

	}
	if(this->r_botton)
	{
		Rect b_door {600, 640, 80, 80};
		env->canvas->draw(b_door, Color::WHITE);
		porta = new Item(this,"porta", 600, 640, true);
		porta->change_sprite("res/tile_sheets/porta4.png");
		porta->set_w(80);
		porta->set_h(80);
		add_child(porta);

	}

}

