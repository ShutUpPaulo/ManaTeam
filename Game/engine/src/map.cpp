#include "map.h"

using namespace std;

// Insert Room
Map::room * Map::InsertRoom(int id, room * left, room * top, room * right, room * bot)
{
	room * newRoom = (room*) malloc(sizeof(room));
	newRoom->left = left;
	newRoom->right = right;
	newRoom->top = top;
	newRoom->bot = bot;
	newRoom->id = id;
    newRoom->hasMap = false;
	
	return newRoom;
}

// Room Criation
void Map::CreateRoom(room *rooms, int id, int x, int y)
{
	int randomVar;
	
	
	randomVar = rand() % 4+1;
	printf("random: %d\n", randomVar);
	switch(randomVar)
	{	
		case LEFT:
			if(rooms->left != NULL)
				CreateRoom(rooms->left, id, x-1, y);
			else if(x-1 >= 0 && matriz[x-1][y] == false)
            {
				rooms->left = InsertRoom(id, NULL, NULL, rooms, NULL);
                matriz[x-1][y] = true;
            }
            else
            {
                printf("abortou sala %d\n", id);
                return;
            }
			break;
			
		case RIGHT:
			if(rooms->right != NULL)
				CreateRoom(rooms->right, id, x+1, y);
			else if(x+1 < 5 && matriz[x+1][y] == false)
            {
				rooms->right = InsertRoom(id, rooms, NULL, NULL, NULL);
                matriz[x+1][y] = true;
            }
            else
            {
                printf("abortou sala %d\n", id);
                return;
            }
			break;
		
		case TOP:
			if(rooms->top != NULL)
				CreateRoom(rooms->top, id, x, y-1);
			else if(y-1 >= 0 && matriz[x][y-1] == false)
            {
				rooms->top = InsertRoom(id, NULL, NULL, NULL, rooms);
                matriz[x][y-1] = true;
            }
            else
            {   
                printf("abortou sala %d\n", id);
                return;
            }
			break;
		
		case BOTTOM:
			if(rooms->bot != NULL)
				CreateRoom(rooms->bot, id, x, y+1);
			else if(y+1 < 5 && matriz[x][y+1] == false)
            {
				rooms->bot = InsertRoom(id, NULL, rooms, NULL, NULL);
                matriz[x][y+1] = true;
            }
            else
            {
                printf("abortou sala %d\n", id);
                return;
            }
			break;
	}
}

// Delete rooms
void Map::ResetMap(room *rooms)
{
	if(rooms->left != NULL)
		ResetMap(rooms->left);
	if(rooms->top != NULL)
		ResetMap(rooms->top);
	if(rooms->right != NULL)
		ResetMap(rooms->right);
	if(rooms->bot != NULL)
		ResetMap(rooms->bot);
		
	free(rooms);
}

// Generate all the map
Map::room * Map::GenerateMap()
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
    
	
	room *rooms = InsertRoom(id, NULL, NULL, NULL, NULL);
	matriz[2][2] = true;
	for(id = 1;id <= MAX; id++)
	{	
		CreateRoom(rooms, id, x, y);
        printf("sala %d criada.\n", id);
        
	}

    return rooms;
}

