/*
 * Classe que representa o sprite do teste.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef PLAYER_H
#define PLAYER_H

#include "core/sprite.h"
#include "map.h"

using std::pair;

class Player : public Sprite
{
public:
    typedef enum { NONE, IDLE, RUNNING } State;
    typedef enum { MOVED, STOPPED } Event;
    typedef enum { LEFT, UP, RIGHT, DOWN } Direction;

    Player(Object *parent, const string& id, Map *current_map);
    ~Player();

    Direction direction() const;
    void set_direction(Direction direction);

    const pair<double, double>& moviment() const;
    void set_moviment(double xaxis, double yaxis);

    static ActionID hitExitDoorID;

    void set_current(Room *room, int x, int y);

    double life();
    double sanity();
    double strength();

    void set_life(double life = 100.0);
    void set_sanity(double sanity = 100.0);
    void set_strength(double strength = 0.0);

    void set_key(bool input);
    void get_key();
    bool has_key();

private:
    class Impl;
    unique_ptr<Impl> m_impl;
    bool m_key = false;

};

#endif
