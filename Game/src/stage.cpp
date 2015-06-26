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

#include "stage.h"
#include "item.h"
#include "map.h"
#include "player.h"


ActionID Stage::colisionID = "colisionID()";

Stage::Stage(ObjectID id)
    : Level(id)
{
    char aux[3];
    *aux = *(id.c_str() + 5);
    printf("aux: %s\n", aux);
    m_num_id = atoi(aux);
    printf("%d\n", m_num_id);

    int quantidade_de_salas = 3 + m_num_id + (m_num_id - 1) * 2;
    m_map = new Map(quantidade_de_salas);
    add_child(m_map);

    m_player = new Player(this, "player", m_map);
    m_player->set_strength(100.0);
    m_player->set_position(600, 320);
    m_player->add_observer(this);

    add_child(m_player);

    Environment *env = Environment::get_instance();
    env->music->play("res/sounds/Fase1.ogg", -1);

    add_observer(m_player);
    add_observer(m_map);
}

void
Stage::update_self(unsigned long)
{
//printf("\n\nPlayer: (%.1f, %.1f) -- %.1f x %.1f\n", m_player->x(), m_player->y(), m_player->w(), m_player->h());
    const list<Object *> itens = m_map->itens();
    for (auto item : itens)
    {
//printf("\n\nItem [%s]: (%.1f, %.1f) -- %.1f x %.1f\n", item->id().c_str(), item->x(), item->y(), item->w(), item->h());
        Rect a = m_player->bounding_box();
        Rect b = item->bounding_box();
        Rect c = a.intersection(b);

        //tratando colisoes diretas
        if(item->walkable() == false)
        {
            
            if(item->id() == "parede_top")
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
                    if(m_player->strength() < item->mass())
                    {
                        if(a.x() < b.x())
                        {
                            m_player->set_x(b.x() - a.w());
                        }
                        else if(a.x() > b.x())
                        {
                            m_player->set_x(b.x() + b.w());
                        }
                    }
                    else
                    {
                        //cout << "Massa do item: " << item->mass() << endl;
                        if(a.x() < b.x())
                        {
                            item->set_x(b.x() + 1);
                        }
                        else if(a.x() > b.x())
                        {
                            item->set_x(b.x() - 1);
                        }   
                    }
                }
                else
                {
                //eixo y
                    if(m_player->strength() < item->mass())
                    {
                        if(a.y() < b.y())
                        {
                            m_player->set_y(b.y() - a.h());
                        }
                        else if(a.y() > b.y())
                        {
                            m_player->set_y(b.y() + b.h());
                        }
                    }
                    else if(m_player->strength() >= item->mass())
                    {
                        //cout << "Massa do item: " << item->mass() << endl;
                        if(a.y() < b.y())
                        {
                            item->set_y(b.y() + 1);
                        }
                        else if(a.y() > b.y())
                        {
                            item->set_y(b.y() - 1);
                        }
                    }
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
                
                if(item->id() == "key")
                {
                    printf("Pegou a chave!\n");
                    m_map->remove_item(item);
                    m_player->get_key();
                }

                if(item->id() == "finalDoor")
                {
                    if(m_player->has_key() == true)
                    {
                        finish();
                        char new_stage[256];
                        sprintf(new_stage, "stage%d", m_num_id+1);
                        m_player->notify(Player::hitExitDoorID, new_stage);
                    }
                }
            }
            if(c.w() > 60 and c.h() > 60)
            {
                if(item->id().find("sala"))
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
                        m_player->set_current(m_map->current_room->r_botton, m_player->x(), 80);
                    }
                }

            }
        }

        //Tratando visoes dos guardas
        if(item->id() == "guard")
        {
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

    return false;
}
