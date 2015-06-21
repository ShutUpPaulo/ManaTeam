
#include <string>
#include <iostream>
#include <core/font.h>
#include <core/environment.h>
#include <core/rect.h>
#include <core/canvas.h>

#include "item.h"
#include "room.h"
#include "guard.h"

Room::Room(Object *parent, ObjectID id, string type)
: Object(parent, id), r_left(nullptr), r_right(nullptr), r_top(nullptr), r_botton(nullptr), type(type),
    m_doors(false)
{
	

	Item *piso;
	char str_piso[256]; 
	for(int i = 1; i < 15; i++)
	{
		for(int j = 1; j < 8; j++)
		{
			sprintf(str_piso, "piso%d%d", i, j);
			piso = new Item(this,str_piso,i*80,j*80,80,80,true);
			piso->change_sprite("res/tile_sheets/tile1.png");
	 		add_child(piso);
		}
	}

	 /*Adicionando cantos*/
	Item *canto;
	canto = new Item(this,"canto01", 0, 0, 80, 80, false);
	canto->change_sprite("res/tile_sheets/canto1.png");
	add_child(canto);

	canto = new Item(this,"canto02", 1200, 0, 80, 80, false);
	canto->change_sprite("res/tile_sheets/canto2.png");
	add_child(canto);

	canto = new Item(this,"canto03", 0, 640, 80, 80, false);
	canto->change_sprite("res/tile_sheets/canto4.png");
	add_child(canto);

	canto = new Item(this,"canto04", 1200, 640, 80, 80, false);
	canto->change_sprite("res/tile_sheets/canto3.png");
	add_child(canto);

	randomize_items();

	Guard *guard = new Guard(this,"guard",rand()%1120+80,rand()%540+80, false);
	add_child(guard);
	//draw_itens(this);
}

string Room::room_type()
{
	if (this->type == "CelaH" || this->type == "CelaV")
		return "Cela";

	return this->type;
}

void Room::pre_drawing(const string item_name, string item_type, 
	int percentage, int pos_x, int pos_y, int width, int height, 
	bool walkable)
{
	string item_path;

	if (item_type == "item")
	{
		item_path = "res/items/.png";
		item_path.insert(10, item_name);
	}
		
	else
	{
		item_path = "res/tile_sheets/.png";
		item_path.insert(16, item_name);
	}
		

	if(rand()%100 <= percentage)
	{
		draw_items(item_path, item_name, pos_x, pos_y, width, height, 
			walkable);
	}
}

void Room::randomize_items()
{
	string item_path;
	string item_name;

	int random_number = rand()%100;

	if(rand()%100 <= 50)
		pre_drawing("Bancada1", "tile_sheet", 20, 520, 240, 240, 240, false);
	else	
		pre_drawing("Bancada2", "tile_sheet", 20, 520, 240, 240, 240, false);

	while(random_number <= 40)
	{
		if(random_number <= 20)
			pre_drawing("Cadeira1", "tile_sheet", 100, rand() % 1098 + 80, 
			rand() % 520 + 80, 22, 40, false);
		else
			pre_drawing("Cadeira2", "tile_sheet", 100, rand() % 1098 + 80, 
			rand() % 520 + 80, 22, 40, false);

		random_number = rand()%100;
	}	

	random_number = rand()%100;	

	while(random_number <= 40)
	{
		if(random_number <= 13)
			pre_drawing("CadeiraseMesa1", "tile_sheet", 100, rand() % 1060 + 80, 
				rand() % 480 + 80, 80, 80, false);
		else if(random_number <= 13)	
			pre_drawing("CadeiraseMesa2", "tile_sheet", 100, rand() % 1060 + 80, 
				rand() % 480 + 80, 80, 80, false);
		else
			pre_drawing("CadeiraseMesa3", "tile_sheet", 100, rand() % 1060 + 80, 
				rand() % 480 + 80, 80, 80, false);

		random_number = rand()%100;
	}

	random_number = rand()%100;

	while(random_number <= 40)
	{
		if(random_number <= 20)
			pre_drawing("Mesa1", "tile_sheet", 100, rand() % 1098 + 80, 
			rand() % 520 + 80, 28, 64, false);
		else
			pre_drawing("Mesa2", "tile_sheet", 100, rand() % 1098 + 80, 
			rand() % 520 + 80, 64, 38, false);

		random_number = rand()%100;
	}

	random_number = rand()%100;

	while(random_number <= 70)
	{
		pre_drawing("Papeis", "tile_sheet", 100, rand() % 1098 + 80, rand() % 520 + 80, 51, 30, true);
		random_number = rand()%100;
	}

	random_number = rand()%100;

	if(random_number <= 10)
		pre_drawing("Pill", "item", 100, rand() % 1098 + 80, rand() % 520 + 80, 40, 40, true);

	random_number = rand()%100;

	if(random_number <= 20)
		pre_drawing("Garrafa", "item", 100, rand() % 1098 + 80, rand() % 520 + 80, 10, 40, true);

	random_number = rand()%100;

	if(this->room_type() == "KeyRoom")
	{
		item_path = "res/items/key.png";
		item_name = "key";
		draw_items(item_path, item_name, rand() % 900 + 80, 
			rand() % 500 + 80, 40, 40, true);
	}	


}

void Room::draw_items(string item_path, string item_name, int pos_x, 
	int pos_y, int width, int height, bool walkable)
{
	Item* item = new Item(this, item_name, pos_x, pos_y, width, height, 
		walkable);

	item->change_sprite(item_path);
	add_child(item);
}
	/*if(this->room_type() == "None")
	{

	}
	if(this->room_type() != "Cela")
	{
		//Desenhando uma bancada
		Item* stand_table = new Item(this, "bancada", 520, 240, 240, 240, false);
		if(random_number == 1)
		{
			stand_table->change_sprite("res/tile_sheets/Bancadaa1.png");
			add_child(stand_table);
		}
			
		else if(random_number == 2)
		{
			stand_table->change_sprite("res/tile_sheets/Bancadaa2.png");
			add_child(stand_table);
		}

		random_number = rand()%10+1;
		//Desenhando uma cadeira
		Item *chair = new Item(this, "cadeira", , rand() % 520 + 80, 22, 40, false);
		if(random_number == 1)
		{
			chair->change_sprite("res/tile_sheets/Cadeira1.png");
			add_child(chair);
		}

		chair = new Item(this, "cadeira", rand() % 1098 + 80, rand() % 520 + 80, 22, 40, false);
		random_number = rand()%10+1;
		if(random_number == 2)
		{
			chair->change_sprite("res/tile_sheets/Cadeira2.png");
			add_child(chair);
		}

		//Desenhando cadeira e mesa
		random_number = rand()%10+1;
		Item *chair_n_table = new Item(this, "cadeira e mesa", rand() % 1060 + 80, rand() % 480 + 80, 80, 80, false);
		if(random_number == 1)
		{
			chair_n_table->change_sprite("res/tile_sheets/CadeiraseMesa1.png");
			add_child(chair_n_table);
		}

		random_number = rand()%10+1;
		chair_n_table = new Item(this, "cadeira e mesa", rand() % 1060 + 80, rand() % 480 + 80, 64, 38, false);
		if(random_number == 2)
		{
			chair_n_table->change_sprite("res/tile_sheets/CadeiraseMesa2.png");
			add_child(chair_n_table);
		}

		random_number = rand()%10+1;
		chair_n_table = new Item(this, "cadeira e mesa", rand() % 1060 + 80, rand() % 480 + 80, 80, 80, false);
		if(random_number == 3)
		{
			chair_n_table->change_sprite("res/tile_sheets/CadeiraseMesa3.png");
			add_child(chair_n_table);
		}
	}
	if(this->room_type() == "Cela")
	{
		if(room->type == "CelaH")
		{
			Item *cell_room = new Item(this, "celas", 0, 0, 1280, 720, true);
			cell_room->change_sprite("res/tile_sheets/ConjuntodeCelas.png");
			add_child(cell_room);
		}

	}
	if(this->room_type() == "Final")
	{

	}
	if(this->room_type() == "KeyRoom")
	{
		Item *key = new Item(this, "key", rand() % 900 + 80, rand() % 500 + 80, 32, 32, true);
		key->change_sprite("res/itens/key.png");
		add_child(key);


	}	

}*/

void
Room::add_list(Object  * item)
{
	this->items.push_back(item);
}

const list<Object *>&
Room::get_items()
{
	return children();
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

	if(this->type == "Final")
	{
		if(this->r_right)
		{
			/*Adicionando portas */
			porta = new Item(this,"finalDoor", 0, 320, 80, 80, true);
			porta->change_sprite("res/door/porta1.png");
			add_child(porta);
		}
		else if(this->r_botton)
		{
			porta = new Item(this,"finalDoor", 600, 0, 80, 80, true);
			porta->change_sprite("res/door/porta2.png");
			add_child(porta);
			
		}
		else if(this->r_left)
		{
			porta = new Item(this,"finalDoor", 1200, 320, 80, 80, true);
			porta->change_sprite("res/door/porta3.png");
			add_child(porta);
		

		}
		if(this->r_top)
		{
			porta = new Item(this,"finalDoor", 600, 640, 80, 80, true);
			porta->change_sprite("res/door/porta4.png");
			add_child(porta);
		
		}
	}
	env->canvas->draw(this->type, 1100, 320,Color::WHITE);
}

void
Room::add_door(char direction, int x, int y)
{
    char doorID[128];
    sprintf(doorID, "porta%c%s", direction, id().c_str());
	Item *porta = new Item(this, doorID, x, y, 80, 80, true);

    char door_sprite[256];
    sprintf(door_sprite, "res/tile_sheets/porta%c.png", direction);
	porta->change_sprite(door_sprite);

	add_child(porta);
}

void
Room::remove_item(Object *item)
{
	remove_child(item);
}

/*Item *parede;
	for(int x = 1; x < 15; x++)
	{
		char str_parede[256];
		sprintf(str_parede, "parede0%d", x);
		parede = new Item(this, str_parede, x*80, 0, 80, 80, false);
		parede->change_sprite("res/tile_sheets/parede2.png");
		add_child(parede);

		parede = new Item(this, str_parede, x*80, 640, 80, 80, false);
		parede->change_sprite("res/tile_sheets/parede4.png");
		add_child(parede);

	}
	for(int y = 1; y < 8; y++ )
	{
		char str_parede[256];
		sprintf(str_parede, "parede1%d",y );
		parede = new Item(this, str_parede, 0, y*80, 80, 80, false);
		parede->change_sprite("res/tile_sheets/parede1.png");
		add_child(parede);

		parede = new Item(this, str_parede, 1200, y*80, 80, 80, false);
		parede->change_sprite("res/tile_sheets/parede3.png");
		add_child(parede);
	}*/

void
Room::update_self(unsigned long)
{
    if (not m_doors)
    {
//printf("Atualizando as portas...\n");
	    if (r_left)
	    {
            add_door('l', 0, 320);
            for(int y = 1; y < 8; y++ )
			{
				if(y == 4)
					continue;

				Item *parede;
				char str_parede[256];
				sprintf(str_parede, "parede_left");
				parede = new Item(this, str_parede, 0, y*80, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede1.png");
				add_child(parede);
			}
        }
        else
        {
        	for(int y = 1; y < 8; y++ )
			{
				Item *parede;
				char str_parede[256];
				sprintf(str_parede, "parede_left");
				parede = new Item(this, str_parede, 0, y*80, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede1.png");
				add_child(parede);
			}
        }

        if (r_right)
        {
            add_door('r', 1200, 320);

            for(int y = 1; y < 8; y++ )
			{
				if(y == 4)
					continue;

				Item *parede;
				char str_parede[256];
        		sprintf(str_parede, "parede_right");
				parede = new Item(this, str_parede, 1200, y*80, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede3.png");
				add_child(parede);
			}
        }
        else
        {
        	for(int y = 1; y < 8; y++ )
			{
				Item *parede;
				char str_parede[256];
        		sprintf(str_parede, "parede_right");
				parede = new Item(this, str_parede, 1200, y*80, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede3.png");
				add_child(parede);
			}
        }

        if (r_top)
        {
            add_door('t', 600, 0);

            for(int x = 1; x < 15; x++)
			{
				Item *parede;
				char str_parede[256];
				sprintf(str_parede, "parede_top");
				if(x == 7 || x == 8)
				{
					
					parede = new Item(this, str_parede, 520, 0, 80, 80, false);
					parede->change_sprite("res/tile_sheets/parede2.png");
					add_child(parede);

					parede = new Item(this, str_parede, 680, 0, 80, 80, false);
					parede->change_sprite("res/tile_sheets/parede2.png");
					add_child(parede);
					x++;
					continue;
				}
				parede = new Item(this, str_parede, x*80, 0, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede2.png");
				add_child(parede);
			}


        }
        else
        {
        	for(int x = 1; x < 15; x++)
			{
				Item *parede;
				char str_parede[256];
				sprintf(str_parede, "parede_top");
				parede = new Item(this, str_parede, x*80, 0, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede2.png");
				add_child(parede);
			}
        }

        if (r_botton)
        {
            add_door('b', 600, 640);
            for(int x = 1; x < 15; x++)
			{
				Item *parede;
				char str_parede[256];
				sprintf(str_parede, "parede_bot");
				if(x == 7 || x == 8)
				{
					
					parede = new Item(this, str_parede, 520, 640, 80, 80, false);
					parede->change_sprite("res/tile_sheets/parede4.png");
					add_child(parede);

					parede = new Item(this, str_parede, 680, 640, 80, 80, false);
					parede->change_sprite("res/tile_sheets/parede4.png");
					add_child(parede);
					x++;
					continue;
				}
				
				parede = new Item(this, str_parede, x*80, 640, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede4.png");
				add_child(parede);
			}
        }
        else
        {
        	for(int x = 1; x < 15; x++)
			{
				Item *parede;
				char str_parede[256];
				sprintf(str_parede, "parede_bot");
				parede = new Item(this, str_parede, x*80, 640, 80, 80, false);
				parede->change_sprite("res/tile_sheets/parede4.png");
				add_child(parede);
			}
        }

        m_doors = true;
    }
}
