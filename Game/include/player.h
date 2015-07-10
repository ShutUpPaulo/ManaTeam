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
    typedef enum { NONE, IDLE, RUNNING, DUCK } State;
    typedef enum { MOVED, STOPPED, DUCKING, STANDING } Event;
    typedef enum { LEFT, UP, RIGHT, DOWN } Direction;

    Player(Object *parent, const string& id, Map *current_map);
    ~Player();
    int m_sanity_loss;

    Direction direction() const;
    void set_direction(Direction direction);

    const pair<double, double>& moviment() const;
    void set_moviment(double xaxis, double yaxis);

    static ActionID hitExitDoorID;
    static ActionID jumpNextLevelID;
    static ActionID takeItemID;
    static ActionID openDoorID;
    static ActionID pushItemID;
    static ActionID repeatLevelID;

    void set_current(Room *room, int x, int y);

    double life();
    double sanity();
    double strength();
    double stamina();

    void set_life(double life = 100.0);
    void set_sanity(double sanity = 100.0);
    void set_strength(double strength = 0.0);
    void set_stamina(double stamina = 100.0);

    void set_key(bool input);
    void get_key();
    bool has_key();

    void take_item();
    void jump_level();
    void open_door();
    void push_item();

    void show_life();
    void show_sanity();
    void show_inventory();
    void show_stamina();

private:
    class Impl;
    unique_ptr<Impl> m_impl;
    bool m_key = false;

};

#endif
