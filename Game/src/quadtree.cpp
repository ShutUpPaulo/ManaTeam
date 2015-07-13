#include <iostream>

#include "quadtree.h"

Quadtree::Quadtree(int pLevel, Rect * pBounds)
{
	m_level = pLevel;
	m_bounds = pBounds;

	for(size_t i = 0;  i < m_nodes.size(); i++)
	{
		m_nodes.at(i) = NULL;
	}
}

void 
Quadtree::clear()
{
	m_objects.clear();

	for(size_t i = 0;  i < m_nodes.size(); i++)
	{

		if(m_nodes.at(i) != NULL)
		{
			m_nodes.at(i)->clear();
			m_nodes.at(i) = NULL;
		}
	}

}
void
Quadtree::split()
{
	int subWidth = (int)(m_bounds->h() / 2);
   	int subHeight = (int)(m_bounds->h() / 2);
   	int x = (int)m_bounds->x();
   	int y = (int)m_bounds->y();
 
   	m_nodes[0] = new Quadtree(m_level+1, new Rect(x + subWidth, y, subWidth, subHeight));
   	m_nodes[1] = new Quadtree(m_level+1, new Rect(x, y, subWidth, subHeight));
   	m_nodes[2] = new Quadtree(m_level+1, new Rect(x, y + subHeight, subWidth, subHeight));
   	m_nodes[3] = new Quadtree(m_level+1, new Rect(x + subWidth, y + subHeight, subWidth, subHeight));
}

int
Quadtree::getIndex(Object * pRect)
{
   	int index = -1;
   	double verticalMidpoint = m_bounds->x() + (m_bounds->w() / 2);
   	double horizontalMidpoint = m_bounds->y() + (m_bounds->h() / 2);
 
   // Object can completely fit within the top quadrants
   	bool topQuadrant = (pRect->y() < horizontalMidpoint && pRect->y() + pRect->h() < horizontalMidpoint);
   	// Object can completely fit within the bottom quadrants
   	bool bottomQuadrant = (pRect->y() > horizontalMidpoint);
 
   	// Object can completely fit within the left quadrants
   	if (pRect->x() < verticalMidpoint && pRect->x() + pRect->w() < verticalMidpoint) {
    	if (topQuadrant) {
        	index = 1;
      	}
      	else if (bottomQuadrant) {
	        index = 2;
	      }
	    }
    // Object can completely fit within the right quadrants
    else if (pRect->x() > verticalMidpoint) {
	    if (topQuadrant) {
       		index = 0;
     	}
     	else if (bottomQuadrant) {
       		index = 3;
     	}
   	}
 
   	return index;
}


void 
Quadtree::insert(Object *pRect) {
   	if (m_nodes[0] != NULL)
   	{
    	int index = getIndex(pRect);
 
    	if (index != -1) 
    	{
    		m_nodes[index]->insert(pRect);
       		return;
     	}
   	}
 
   	m_objects.push_back(pRect);
 
   	if ((int)m_objects.size() > MAX_OBJECTS && m_level < MAX_LEVELS) 
   	{
    	if (m_nodes[0] == NULL) { 
         	split(); 
      	}
 
    	int i = 0;
     	while (i < (int)m_objects.size()) 
     	{
       		int index = getIndex(m_objects.at(i));
       		if (index != -1) 
       		{
         		m_nodes[index]->insert(m_objects.at(i));
         		m_objects.erase(m_objects.begin() + i);
       		}
       	else 
       	{
         	i++;
       	}
     }
   }
 }

list<Object*>
Quadtree::retrieve(list<Object*> returnObjects, Object* pRect) {
   	int index = getIndex(pRect);
   	if (index != -1 && m_nodes.at(0) != NULL) 
   	{
     	m_nodes.at(index)->retrieve(returnObjects, pRect);
   	}
 
 	for(size_t i = 0; i < m_objects.size(); i++)
 	{
 		returnObjects.push_back(m_objects.at(i));
 	}
 
   	return returnObjects;
 }