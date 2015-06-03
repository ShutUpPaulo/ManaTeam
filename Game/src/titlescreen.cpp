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

    double bw = 100;
    double bh = 50;

    double bx = (w - bw)/2;
    double by = h/2;

    Button *ok = new Button(this, "ok", bw, bh);
    ok->set_position(bx, by);
    ok->set_color(Color::RED,Color::BLUE);
    Button *exit = new Button(this, "exit", bw, bh);
    exit->set_position(bx, by + bh + 20);
    exit->set_color(Color::WHITE,Color::RED);

    ok->add_observer(this);
    exit->add_observer(this);

    add_child(ok);
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
    }

    finish();

    return true;
}
