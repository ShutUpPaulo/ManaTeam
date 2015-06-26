
#include <string>
#include <iostream>
#include <list>

#include <core/font.h>
#include <core/rect.h>
#include <core/environment.h>
#include <core/canvas.h>
#include <core/image.h>

#include "item.h"
#include "room.h"
#include "guard.h"

static int randint(int a, int b)
{
    int N = b - a + 1;
    int r = rand() % N;

    return a + r;
}

Room::Room(Object *parent, ObjectID id, string type)
: Object(parent, id), r_left(nullptr), r_right(nullptr), r_top(nullptr), r_botton(nullptr), type(type),
    m_doors(false)
{
    fill_floor("tile1");
    add_corners("canto");
    add_guard("guard");
    add_itens();
}

string Room::room_type()
{
	if (this->type == "CelaH" || this->type == "CelaV")
		return "Cela";

	return this->type;
}

void Room::add_itens()
{
    typedef struct _ItemInfo {
        string name;
        string type;
        int variations;
        int weight;
        bool walkable;
        bool unique;
        double mass;
        int x, y;
    } ItemInfo;

    list<ItemInfo> items {
        {"Bancada", "tile_sheet", 2, 20, false, true, INFINITE, 520, 240},
        {"Cadeira", "tile_sheet", 2, 40, false, false, 5.0, -1, -1},
        {"CadeiraseMesa", "tile_sheet", 3, 40, false, 25.0, false, -1, -1},
        {"Mesa", "tile_sheet", 2, 40, false, false, 20.0, -1, -1},
        {"Papeis", "tile_sheet", 0, 70, true, false, 0.0, -1, -1},
        {"Pill", "tile_sheet", 0, 10, true, false, 0.0, -1, -1},
        {"Garrafa", "tile_sheet", 0, 20, true, false, 0.0, -1, -1},
    };

    int total_weight = 0;

    for (auto item : items)
    {
        total_weight += item.weight;
    }

	if (room_type() == "KeyRoom")
	{
		string path = "res/items/key.png";
        Item* item = new Item(this, "key", path, 300, 300, 1.0, true);
        //place(item, 300,300);
        while (not place(item, -1, -1));
        cout << "Entrou!" << cout;
        add_child(item);
	}	

    static const int MAX_ITENS = 15;
    int num_itens = randint(0, MAX_ITENS);

    for (int i = 0; i < num_itens and (not items.empty()); ++i)
    {
        int p = randint(1, total_weight);
        auto it = items.begin();
        int total = it->weight;

        while (p > total)
        {
            ++it;
            total += it->weight;
        }

        char path[512];

        if (it->variations)
        {
            int variation = randint(1, it->variations);
            sprintf(path, "res/tile_sheets/%s%d.png", it->name.c_str(), variation);
        } else
        {
            sprintf(path, "res/tile_sheets/%s.png", it->name.c_str());
        }

        double x = it->x;
        double y = it->y;

        Item* item = new Item(this, it->name, path, x, y, it->mass, it->walkable);

        if (place(item, x, y))
            add_child(item);
        else
            delete item;

        if (it->unique)
        {
            total_weight -= it->weight;
            items.erase(it);
        }
    }
}

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

void
Room::add_door(char direction, int x, int y)
{
    char doorID[128];
    sprintf(doorID, "porta%c%s", direction, id().c_str());
    char door_sprite[256];
    sprintf(door_sprite, "res/tile_sheets/porta%c.png", direction);

	Item *porta = new Item(this, doorID, door_sprite, x, y, INFINITE, true);

	add_child(porta);
}

void
Room::remove_item(Object *item)
{
	remove_child(item);
}

void
Room::update_self(unsigned long)
{
    if (not m_doors)
    {
        Item *porta;
        string path;

	    if (r_left)
	    {
            add_door('l', 0, 320);
            for(int y = 1; y < 8; y++ )
			{
				if(y == 4)
					continue;

				Item *parede;
				char name[256];
				sprintf(name, "parede_left");
                path = "res/tile_sheets/parede1.png";
				parede = new Item(this, name, path, 0, y*80, INFINITE, false);
				add_child(parede);
			}
        }
        else
        {
        	for(int y = 1; y < 8; y++ )
			{
				Item *parede;
				char name[256];
				sprintf(name, "parede_left");
                path = "res/tile_sheets/parede1.png";
				parede = new Item(this, name, path, 0, y*80, INFINITE, false);
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
				char name[256];
        		sprintf(name, "parede_right");
                path = "res/tile_sheets/parede3.png";
				parede = new Item(this, name, path, 1200, y*80, INFINITE, false);
				add_child(parede);
			}
        }
        else
        {
        	for(int y = 1; y < 8; y++ )
			{
				Item *parede;
				char name[256];
        		sprintf(name, "parede_right");
                path = "res/tile_sheets/parede3.png";
				parede = new Item(this, name, path, 1200, y*80, INFINITE, false);
				add_child(parede);
			}
        }

        if (r_top)
        {
            add_door('t', 600, 0);

            for(int x = 1; x < 15; x++)
			{
				Item *parede;
				char name[256];
				sprintf(name, "parede_top");
                string path = "res/tile_sheets/parede2.png";

				if(x == 7 || x == 8)
				{
					parede = new Item(this, name, path, 520, 0, INFINITE, false);
					add_child(parede);

					parede = new Item(this, name, path, 680, 0, INFINITE, false);
					add_child(parede);
					x++;
					continue;
				}
				parede = new Item(this, name, path, x*80, 0, INFINITE, false);
				add_child(parede);
			}


        }
        else
        {
        	for(int x = 1; x < 15; x++)
			{
				char name[256];
				sprintf(name, "parede_top");
                string path = "res/tile_sheets/parede2.png";
				Item *parede = new Item(this, name, path, x*80, 0, INFINITE, false);
				add_child(parede);
			}
        }

        if (r_botton)
        {
            add_door('b', 600, 640);
            for(int x = 1; x < 15; x++)
			{
				Item *parede;
				char name[256];
				sprintf(name, "parede_bot");
                string path = "res/tile_sheets/parede4.png";

				if(x == 7 || x == 8)
				{
					parede = new Item(this, name, path, 520, 640, INFINITE, false);
					add_child(parede);

					parede = new Item(this, name, path, 680, 640, INFINITE, false);
					add_child(parede);
					x++;

					continue;
				}
				
				parede = new Item(this, name, path, x*80, 640, INFINITE, false);
				add_child(parede);
			}
        }
        else
        {
        	for(int x = 1; x < 15; x++)
			{
				char name[256];
				sprintf(name, "parede_bot");
                string path = "res/tile_sheets/parede4.png";
				Item *parede = new Item(this, name, path, x*80, 640, INFINITE, false);
				add_child(parede);
			}
        }

        if(this->type == "Final")
        {
            if(this->r_right)
            {
                // Adicionando portas
                path = "res/door/porta1.png";
                porta = new Item(this,"finalDoor", path, 0, 320, INFINITE, true);
                add_child(porta);
            }
            else if(this->r_botton)
            {
                path = "res/door/porta2.png";
                porta = new Item(this,"finalDoor", path, 600, 0, INFINITE, true);
                add_child(porta);
                
            }
            else if(this->r_left)
            {
                path = "res/door/porta3.png";
                porta = new Item(this,"finalDoor", path, 1200, 320, INFINITE, true);
                add_child(porta);
            }
            if(this->r_top)
            {
                path = "res/door/porta4.png";
                porta = new Item(this,"finalDoor", path, 600, 640, INFINITE, true);
                add_child(porta);
            }
        }

        m_doors = true;
    }
}

void
Room::fill_floor(const string& name)
{
    char path[512];
    sprintf(path, "res/tile_sheets/%s.png", name.c_str());

    Image *image = new Image(nullptr, path);

    if (not image)
    {
        return;
    }

    Environment *env = Environment::get_instance();
    Canvas *canvas = env->canvas;

    int w = canvas->w() / image->w();
    int h = canvas->h() / image->h();

    center_area.set_position(image->w(), image->h());
    center_area.set_dimensions(canvas->w() - 2*image->w(), canvas->h() - 2*image->h());

    for(int i = 1; i < w - 1; i++)
	{
		for(int j = 1; j < h - 1; j++)
		{
			Item *floor = new Item(this, "floor", path, i*image->w(), j*image->h(), INFINITE, true);
	 		add_child(floor);
		}
	}

    delete image;
}

void
Room::add_corners(const string& name)
{
    Environment *env = Environment::get_instance();
    Canvas *canvas = env->canvas;

    for (int i = 0; i < 4; ++i)
    {
        char path[512];
        sprintf(path, "res/tile_sheets/%s%d.png", name.c_str(), i + 1);

        Image *image = new Image(nullptr, path);

        if (not image)
            continue;

        double x = i % 3 ? canvas->w() - image->w() : 0;
        double y = i/2 ? canvas->h() - image->h() : 0;

        delete image;

	    Item *corner = new Item(this, "corner", path, x, y, INFINITE, false);
	    add_child(corner);
    }
}

void
Room::add_guard(const string& name)
{
	Guard *guard = new Guard(this, name, 0, 0, 60, false);
    place(guard, -1, -1);
	add_child(guard);
}

bool
Room::place(Object *object, double x, double y)
{
    int w = center_area.w();
    int h = center_area.h();

    int tries = 0;
    bool ok, randomize = x < 0 and y < 0;

    do {
        ok = true;
        ++tries;

        if (randomize)
        {
            x = (rand() % w) + center_area.x();
            y = (rand() % h) + center_area.y();
        }

        if (x + object->w() > w + center_area.x())
            x = w + center_area.x() - object->w();

        if (y + object->h() > h + center_area.y())
            y = h + center_area.y() - object->h();

        for (auto obj : children())
        {
            if (obj->walkable())
                continue;

            Rect a { x, y, object->w(), object->h() };
            Rect b = obj->bounding_box();
            Rect c = a.intersection(b);
            
            if (c.w() or c.h())
            {
                ok = false;
                break;
            }
        }

        if (tries > 10)
            break;

    } while (not ok and randomize);
        
    object->set_position(x, y);

    return ok;
}
