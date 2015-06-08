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

#include "stage.h"
#include "item.h"
#include "map.h"
#include "player2.h"


ActionID Stage::colisionID = "colisionID()";

Stage::Stage(ObjectID id)
    : Level(id)
{
    char aux[3];
    *aux = *(id.c_str() + 5);
    printf("aux: %s\n", aux);
    m_num_id = atoi(aux);
    printf("%d\n", m_num_id);

    int quantidade_de_salas = 30 + m_num_id + (m_num_id - 1) * 2;
    m_map = new Map(quantidade_de_salas);
    add_child(m_map);

    m_player = new Player2(this, "player", m_map);
    m_player->set_position(600, 320);
    m_player->add_observer(this);

    add_child(m_player);

    Environment *env = Environment::get_instance();
    env->music->play("res/sounds/Fase1.ogg", -1);
//    env->sfx->play("res/sounds/Alarme2.ogg", 1);

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

        if (c.w() != 0 and c.h() != 0)
        {
            char message[512];
            sprintf(message, "%s,%s,%.2f,%.2f,%.2f,%.2f", m_player->id().c_str(), item->id().c_str(), c.x(),
                c.y(), c.w(), c.h());

            notify(Stage::colisionID, message);
            //printf("Player acertou o item [%s]\n", item->id().c_str(), item->x(), item->y());

            if(item->id() == "key")
            {
                printf("Pegou a chave!\n");
                m_map->remove_item(item);
            }
            if(item->id() == "finalDoor")
            {
                finish();
                char new_stage[256];
                sprintf(new_stage, "stage%d", m_num_id+1);
                m_player->notify(Player2::hitExitDoorID, new_stage);
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
    if (id == Player2::hitExitDoorID)
    {
        set_next(p);
        finish();
        return true;
    }

    return false;
}
