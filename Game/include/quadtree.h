#ifndef QUADTREE_H
#define QUADTREE_H

#include <core/rect.h>
#include <vector>
#include <core/object.h>
#include <array>

using namespace std;
using std::vector;
using std::array;
using std::list;
class Quadtree
{
public:
    Quadtree(int pLevel, Rect *pBounds);
    ~Quadtree();

    void clear();
    void split();
    int getIndex(Object *rect);
    void insert(Object *rect);
    list<Object*> retrieve(list<Object*> returnObj, Object *rect);


private:
	int MAX_OBJECTS = 5;
	int MAX_LEVELS = 10;
	int m_level;
	vector <Object *> m_objects;
	array<Quadtree*,4> m_nodes;
	Rect *m_bounds;
};

#endif
