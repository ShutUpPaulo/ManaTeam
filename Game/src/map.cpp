#include <list>
#include <utility>
#include <ijengine/core/environment.h>
#include <ijengine/core/rect.h>
#include <map>

#include "map.h"


using namespace std;

Map::Map(int qnt_salas) : current_room(nullptr)
{	
	GenerateMap(qnt_salas);

}
// Room Criation
void Map::CreateRoom(Room *room, int *id,int x, int y, int qnt)
{
	int randomVar;
    int randomType = rand() % 3; 
    string type;
    int num = *id;
    char numero1, numero2;
	
	randomVar = rand() % 4+1;

	string sala = "sala ";

	numero1 = num/10 + 48;
	numero2 = num % 10 + 48;

    if(randomType < 2)
        type = "None";
    else if (randomType < 3)
        type = "Cela";
    if(*id == (int)(qnt*0.5))
        type = "KeyRoom";
    if(*id == (int)(qnt*0.9))
        type = "Final";



    if(room->type == "Final")
    {
        *id-=1;
        return;
    }
    
	switch(randomVar)
	{	
		case LEFT:
			if(room->r_left != nullptr)
				CreateRoom(room->r_left, id, x-1, y, qnt);
			else if(x-1 >= 0 && matriz[x-1][y] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_right)))
            {
                if(type == "Cela")
                    type += 'H';

            	room->Room::r_left = new Room(this, sala + numero1 + numero2, type);
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
				CreateRoom(room->r_right, id, x+1, y, qnt);
			else if(x+1 < qnt && matriz[x+1][y] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_left)))
            {
                if(type == "Cela")
                    type += 'H';

            	room->r_right = new Room(this, sala + numero1 + numero2, type);
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
				CreateRoom(room->r_top, id, x, y-1, qnt);
			else if(y-1 >= 0 && matriz[x][y-1] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_botton)))
            {
                if(type == "Cela")
                    type += 'V';
                
				room->r_top = new Room(this, sala + numero1 + numero2, type);
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
				CreateRoom(room->r_botton, id, x, y+1, qnt);
			else if(y+1 < qnt && matriz[x][y+1] == false && (room->room_type() != "Cela" || (room->room_type() == "Cela" && room->r_top)))
            {
                if(type == "Cela")
                    type += 'V';
                
				room->r_botton = new Room(this, sala + numero1 + numero2, type);
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
void Map::GenerateMap(int quantidade_salas)
{
    srand(time(NULL));
	
    int x = rand() % quantidade_salas/2 + 1;
    int y = x;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            matriz[i][j] = false;
        }
    }

	Room *room = new Room(this, "sala 00", "None");
    current_room = room;

	matriz[x][y] = true;

	for(int id = 1; id < quantidade_salas; id++)
	{	
		CreateRoom(room, &id, x, y, quantidade_salas);
	}
//    add_child(current_room);
}

Room *
Map::room()
{
	return current_room;
}

void
Map::set_current(Room *nova)
{
	current_room = nova;
}

void Map::draw_self()
{
    if (current_room)
        current_room->draw();
}

const list<Object *>&
Map::itens() const
{
    return current_room->get_itens();
}

void
Map::update_self(unsigned long elapsed)
{
    current_room->update(elapsed);
}
