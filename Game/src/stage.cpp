/*
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <core/environment.h>
#include <core/music.h>
#include <core/soundeffect.h> 
#include <core/audiomanager.h>
#include <core/audiomanagerwrapper.h>

#include <cmath>

#include "guard.h"
#include "stage.h"
#include "item.h"
#include "map.h"
#include "player.h"


ActionID Stage::colisionID = "colisionID()";

Stage::Stage(ObjectID id)
    : Level(id)
{
    char aux[10];
    char temp[10];
    sprintf(temp, "%s", id.c_str());
    for(int i = 0; temp[i] != '\0'; i++)
    {
        aux[i] = temp[i+5];
    }

    printf("%s\n", aux);
    m_num_id = atoi(aux);
    cout << m_num_id << endl;
    int quantidade_de_salas = 3 + m_num_id + (m_num_id - 1) * 2;
    m_map = new Map(quantidade_de_salas,m_num_id);
    add_child(m_map);

    double life = 100.0;

    m_player = new Player(this, "player", m_map);
    m_player->set_strength(100.0);
    m_player->set_life(life);
    m_player->set_position(600, 320);
    m_player->add_observer(this);
    m_player->set_key(false);

    add_child(m_player);

    Environment *env = Environment::get_instance();
    env->music->play("res/sounds/Fase1.ogg", -1);

    add_observer(m_player);
    add_observer(m_map);
}

void
Stage::update_self(unsigned long)
{
    const list<Object *> items = m_map->items();
    for (auto item : items)
    {
        Rect a = m_player->bounding_box();
        Rect b = item->bounding_box();
        Rect c = a.intersection(b);

        //tratando colisoes diretas
        if(item->walkable() == false)
        {
            if(item->id() == "paredet")
            {
                if (c.w() != 0 and c.h() > 50)
                {
                    char message[512];
                    sprintf(message, "%s,%s,%.2f,%.2f,%.2f,%.2f", m_player->id().c_str(), item->id().c_str(), c.x(),
                        c.y(), c.w(), c.h());
                    notify(Stage::colisionID, message);

                    if(a.y() > b.y())
                    {
                        m_player->set_y(b.y() + b.h() - 50);
                    }
                }
            }
            else if (c.w() != 0 and c.h() != 0)
            {
                char message[512];
                sprintf(message, "%s,%s,%.2f,%.2f,%.2f,%.2f", m_player->id().c_str(), item->id().c_str(), c.x(),
                    c.y(), c.w(), c.h());
                notify(Stage::colisionID, message);

                //eixo x
                if(abs(a.x() - b.x()) > abs(a.y() - b.y()))
                {
                    // if(m_player->strength() < item->mass())
                    // {
                        if(a.x() < b.x())
                        {
                            m_player->set_x(b.x() - a.w() + 1);
                        }
                        else if(a.x() > b.x())
                        {
                            m_player->set_x(b.x() + b.w() - 1);
                        }
                    // }
                    // else
                    // {
                    //     //cout << "Massa do item: " << item->mass() << endl;
                    //     if(a.x() < b.x())
                    //     {
                    //         item->set_x(b.x() + 1);
                    //         m_player->set_x(b.x() - a.w());
                    //     }
                    //     else if(a.x() > b.x())
                    //     {
                    //         item->set_x(b.x() - 1);
                    //         m_player->set_x(b.x() + b.w());
                    //     }   
                    // }
                }
                else
                {
                //eixo y
                    // if(m_player->strength() < item->mass())
                    // {
                        if(a.y() < b.y())
                        {
                            m_player->set_y(b.y() - a.h() + 1);
                        }
                        else if(a.y() > b.y())
                        {
                            m_player->set_y(b.y() + b.h() - 1);
                        }
                    // }
                    // else if(m_player->strength() >= item->mass())
                    // {
                    //     //cout << "Massa do item: " << item->mass() << endl;
                    //     if(a.y() < b.y())
                    //     {
                    //         item->set_y(b.y() + 1);
                    //         m_player->set_y(b.y() - a.h());
                    //     }
                    //     else if(a.y() > b.y())
                    //     {
                    //         item->set_y(b.y() - 1);
                    //         m_player->set_y(b.y() + b.h());
                    //     }
                    // }
                }
            }
        }
        else
        {

            if (c.w() != 0 and c.h() != 0)
            {
                char message[512];
                sprintf(message, "%s,%s,%.2f,%.2f,%.2f,%.2f", m_player->id().c_str(), item->id().c_str(), c.x(),
                    c.y(), c.w(), c.h());

                notify(Stage::colisionID, message);
                
                // if(item->id() == "key")
                // {
                //     printf("Pegou a chave!\n");
                //     m_map->remove_item(item);
                //     m_player->get_key();
                // }

                // if(item->id() == "finalDoor")//"res/door/portal.png" ||item->id() == "res/door/portat.png" || item->id() =="res/door/portar.png" || item->id() =="res/door/portab.png")
                // {
                //     if(m_player->has_key() == true)
                //     {
                //         m_player->set_key(false);
                //         finish();
                //         char new_stage[256];
                //         sprintf(new_stage, "stage%d", m_num_id+1);
                //         m_player->notify(Player::hitExitDoorID, new_stage);
                //     }
                //     else
                //     {

                //     }
                // }
            }
            if(c.w() > 50 and c.h() > 50)
            {
                if(item->id() == "door") //"res/tile_sheets/portal.png" ||item->id() == "res/tile_sheets/portat.png" || item->id() =="res/tile_sheets/portar.png" || item->id() =="res/tile_sheets/portab.png")
                {
                    if(item->x() == 0 && item->y() == 320)
                    {
                        m_player->set_current(m_map->current_room->r_left, 1120, m_player->y());
                    }
                    else if(item->x() == 1200 && item->y() == 320)
                    {
                        m_player->set_current(m_map->current_room->r_right, 80, m_player->y());
                    }
                    else if(item->x() == 600 && item->y() == 0)
                    {
                        m_player->set_current(m_map->current_room->r_top, m_player->x(), 560);
                    }
                    else if(item->x() == 600 && item->y() == 640)
                    {
                        m_player->set_current(m_map->current_room->r_bottom, m_player->x(), 80);
                    }
                }

            }
        }

        //Tratando visoes dos guardas
        if(item->id() == "guard")
        {
            Guard *guarda = (Guard*) item;
            guarda->get_playerx(m_player->x());
            guarda->get_playery(m_player->y());
            const list<Object *> filhos = item->children();

            for (auto filho : filhos)
            {
                Rect a2 = m_player->bounding_box();
                Rect b2 = filho->bounding_box();
                Rect c2 = a2.intersection(b2);

                if (c2.w() != 0 and c2.h() != 0)
                {
                    if(filho->id() == "visao")
                    {
                        //cout << "voce foi visto!" << endl;
                        /*double life = m_player->set_life();
                        life--;
                        if(life <= 0)
                            cout << "Game Over" << endl;
                        */
                    }
                }
            }
        }
    }
}

void
Stage::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::BLUE);   
}

bool
Stage::on_message(Object *, MessageID id, Parameters p)
{
    if (id == Player::hitExitDoorID)
    {
        set_next(p);
        finish();
        return true;
    }
    else if(id == Player::jumpNextLevelID)
    {
        m_player->set_key(false);
        finish();
        char new_stage[256];
        sprintf(new_stage, "stage%d", m_num_id+1);
        m_player->notify(Player::hitExitDoorID, new_stage);
        return true;
    }
    else if(id == Player::takeItemID)
    {
        const list<Object *> items = m_map->items();
        for (auto item : items)
        {
            Rect a = m_player->bounding_box();
            Rect b = item->bounding_box();
            Rect c = a.intersection(b);

            //tratando colisoes diretas
            if(item->walkable() == true)
            {
                if(item->id() == "key")
                {
                    if (c.w() != 0 and c.h() != 0)
                    {
                        printf("Pegou a chave!\n");
                        m_map->remove_item(item);
                        m_player->get_key();
                        return true;
                    }
                }
            }
        }
    }
    else if(id == Player::openDoorID)
    {
        const list<Object *> items = m_map->items();
        for (auto item : items)
        {
            Rect a = m_player->bounding_box();
            Rect b = item->bounding_box();
            Rect c = a.intersection(b);

            if(item->walkable() == true)
            {
                if(item->id() == "finalDoor")
                {
                    if (c.w() > 0 and c.h() > 0)
                    {
                        if(m_player->has_key() == true)
                        {
                            m_player->set_key(false);
                            finish();
                            char new_stage[256];
                            sprintf(new_stage, "stage%d", m_num_id+1);
                            m_player->notify(Player::hitExitDoorID, new_stage);
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if(id == Player::pushItemID)
    {
        const list<Object *> items = m_map->items();
        for (auto item : items)
        {
            Rect a = m_player->bounding_box();
            Rect b = item->bounding_box();
            Rect c = a.intersection(b);

            if(item->walkable() == false)
            {
                if (c.w() != 0 and c.h() != 0)
                {
                    if(item->mass() <= m_player->strength())
                    {
                        if(abs(a.x() - b.x()) > abs(a.y() - b.y()))
                        {
                            if(a.x() < b.x())
                            {
                                item->set_x(b.x() + 1);
                                //m_player->set_x(b.x() - a.w());
                            }
                            else if(a.x() > b.x())
                            {
                                item->set_x(b.x() - 1);
                                //m_player->set_x(b.x() + b.w());
                            } 
                        }
                        else
                        {  
                            if(a.y() < b.y())
                            {
                                item->set_y(b.y() + 1);
                                //m_player->set_y(b.y() - a.h());
                            }
                            else if(a.y() > b.y())
                            {
                                item->set_y(b.y() - 1);
                                //m_player->set_y(b.y() + b.h());
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
