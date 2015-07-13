#include "pause.h"

#include <ijengine/util/button.h>
#include <core/font.h>
#include <core/environment.h>

#include <iostream>
using namespace std;

Pausa::Pausa()
    : Level("pausa")
{
    Environment *env = Environment::get_instance();

    double w = env->canvas->w();
    double h = env->canvas->h();

    set_dimensions(w, h);

    Button *backGame = new Button(this, "backGame", "res/interface/menuPausa/voltarJogo.png",
        "res/interface/menuPausa/SvoltarJogo.png");
    backGame->align_to(this, Object::RIGHT, Object::NONE);
    backGame->set_y(200);

    Button *backMenu = new Button(this, "backMenu", "res/interface/menuExtras/voltar.png",
        "res/interface/menuExtras/Svoltar.png");
    backMenu->align_to(this, Object::RIGHT, Object::NONE);
    backMenu->set_y(backGame->y() + backGame->h()+20);

    Button *exit = new Button(this, "exit", "res/interface/menuExtras/sair.png",
        "res/interface/menuExtras/Ssair.png");
    exit->align_to(this, Object::RIGHT, Object::NONE);
    exit->set_y(backGame->y() + backGame->h()+20);

    backGame->add_observer(this);
    backMenu->add_observer(this);
    exit->add_observer(this);

    add_child(backGame);
    add_child(backMenu);
    add_child(exit);

}

Pausa::~Pausa()
{
}

void
Pausa::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);

    shared_ptr<Texture> image = env->resources_manager->get_texture("res/interface/menuPausa/fundoPausa.png");
    env->canvas->draw(image.get(), 1, 0);
}

bool
Pausa::on_message(Object *object, MessageID id, Parameters)
{
    Environment *env = Environment::get_instance();

    if (id != Button::clickedID)
    {
        return false;
    }

    Button *button = dynamic_cast <Button *>(object);

    if (not button)
    {
        return false;
    }
    if (button->id() == "backGame")
    {
        return false;
    } else if (button->id() == "backMenu")
    {
        set_next("title");
    }

    finish();

    return true;
}
