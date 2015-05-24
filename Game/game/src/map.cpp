#include "map.h"

#include <vector>
#include <utility>
#include <ijengine/core/environment.h>
#include <ijengine/core/rect.h>

using namespace std;

Map::Map()
{	
	/*Room *room = new Room(this, "room");
	add_child(room);*/
	GenerateMap();
}
// Room Criation
void Map::CreateRoom(Room *room, int *id,int x, int y)
{
	int randomVar;
	
	randomVar = rand() % 4+1;

	switch(randomVar)
	{	
		case LEFT:
			if(room->r_left != nullptr)
				CreateRoom(room->r_left, id, x-1, y);
			else if(x-1 >= 0 && matriz[x-1][y] == false)
            {
            	room->Room::r_left = new Room(this, "salaEsq");
            	room->r_left->r_right = room;
				//rooms->left = InsertRoom(*id, NULL, NULL, rooms, NULL);
                matriz[x-1][y] = true;
                //add_child(room->r_left);
                //*id+=1;
            }	
            else
            {
                *id-=1;
                return;
            }
			break;
			
		case RIGHT:
			if(room->r_right != nullptr)
				CreateRoom(room->r_right, id, x+1, y);
			else if(x+1 < 5 && matriz[x+1][y] == false)
            {
            	room->r_right = new Room(this, "salaDir");
            	room->r_right->r_left = room;
				//rooms->right = InsertRoom(*id, rooms, NULL, NULL, NULL);
                matriz[x+1][y] = true;
                //add_child(room->r_right);
                //*id+=1;
            }
            else
            {   
                *id-=1;
                return;
            }
			break;
		
		case TOP:
			if(room->r_top != nullptr)
				CreateRoom(room->r_top, id, x, y-1);
			else if(y-1 >= 0 && matriz[x][y-1] == false)
            {
				room->r_top = new Room(this, "salaCim");
				room->r_top->r_botton = room;
                matriz[x][y-1] = true;
                //add_child(room->r_top);
                //*id+=1;
            }
            else
            {   
                *id-=1;
                return;
            }
			break;
		
		case BOTTOM:
			if(room->r_botton != nullptr)
				CreateRoom(room->r_botton, id, x, y+1);
			else if(y+1 < 5 && matriz[x][y+1] == false)
            {
				room->r_botton = new Room(this, "salaBai");
				room->r_botton->r_top = room;
                matriz[x][y+1] = true;
                //add_child(room->r_botton);
                //*id+=1;
            }
            else
            {
                *id-=1;
                return;
            }
			break;
	}
}


// Generate all the map
void Map::GenerateMap()
{
	int id = 0;
    int x = 2;
    int y = x;
    srand(time(NULL));

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            matriz[i][j] = false;
        }
    }
    printf("Gerou a matriz\n");
	Room *room = new Room(this,"sala");
	add_child(room);
	matriz[2][2] = true;
    id+=1;
	for(id = 1;id < MAX; id++)
	{	
		CreateRoom(room, &id, x, y);
	}
    printf("saindo da generate\n");
}

void Map::draw_self()
{
	const Color color {0, 200, 60 };

	Rect r {200, 200, 100, 50};

    Environment *env = Environment::get_instance();
    //env->canvas->clear(Color::BLUE);
    env->canvas->draw(r,color);
}