/*
 * Implementação da classe TitleScreen.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "titlescreen.h"
 
#include <ijengine/util/button.h>
#include <core/font.h>
#include <core/environment.h>

#include <iostream>
using namespace std;

TitleScreen::TitleScreen()
    : Level("title")
{
    Environment *env = Environment::get_instance();

    double w = env->canvas->w();
    double h = env->canvas->h();

    set_dimensions(w, h);

    Button *ok = new Button(this, "ok", "res/buttons/new-game.png",
        "res/buttons/new-game-selected.png");
    ok->align_to(this, Object::CENTER, Object::MIDDLE);

    Button *settings = new Button(this, "settings", "res/buttons/set-up.png",
        "res/buttons/set-up-selected.png");
    settings->align_to(this, Object::CENTER, Object::NONE);
    settings->set_y(ok->y() + ok->h() + 20);

    Button *exit = new Button(this, "exit", "res/buttons/exit.png",
        "res/buttons/exit-selected.png");
    exit->align_to(this, Object::CENTER, Object::NONE);
    exit->set_y(settings->y() + settings->h() + 20);

    ok->add_observer(this);
    settings->add_observer(this);
    exit->add_observer(this);

    add_child(ok);
    add_child(settings);
    add_child(exit);
}

TitleScreen::~TitleScreen()
{
}

void
TitleScreen::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);

    shared_ptr<Texture> image = env->resources_manager->get_texture("res/images/menuBackground.png");
    env->canvas->draw(image.get(), 1, 0);
}

bool
TitleScreen::on_message(Object *object, MessageID id, Parameters)
{
    if (id != Button::clickedID)
    {
        return false;
    }

    Button *button = dynamic_cast<Button *>(object);

    if (not button)
    {
        return false;
    }

    if (button->id() == "ok")
    {
        set_next("stage1");
    } else if (button->id() == "settings")
    {
        //set_next("options");
    }

    finish();

    return true;
}
