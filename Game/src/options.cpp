#include "options.h"
 
#include <ijengine/util/button.h>
#include <core/font.h>
#include <core/environment.h>

#include <iostream>
using namespace std;

Options::Options()
    : Level("options")
{
    Environment *env = Environment::get_instance();

    double w = env->canvas->w();
    double h = env->canvas->h();

    set_dimensions(w, h);

    Button *set_fullscreen = new Button(this, "fullscreen", "res/interface/menuOpcao/modoJanela.png",
        "res/interface/menuOpcao/SmodoJanela.png");
    set_fullscreen->align_to(this, Object::RIGHT, Object::MIDDLE);

    Button *windowmode = new Button(this, "windowmode", "res/interface/menuOpcao/comoJogar.png",
        "res/interface/menuOpcao/ScomoJogar.png");
    windowmode->align_to(this, Object::RIGHT, Object::NONE);
    windowmode->set_y(set_fullscreen->y() + set_fullscreen->h() + 20);

    Button *back = new Button(this, "back", "res/interface/menuOpcao/voltar.png",
        "res/interface/menuOpcao/Svoltar.png");
    back->align_to(this, Object::RIGHT, Object::NONE);
    back->set_y(windowmode->y() + windowmode->h() + 20);

    set_fullscreen->add_observer(this);
    windowmode->add_observer(this);
    back->add_observer(this);

    add_child(set_fullscreen);
    add_child(windowmode);
    add_child(back);
}

Options::~Options()
{
}

void
Options::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);

    shared_ptr<Texture> image = env->resources_manager->get_texture("res/interface/menuOpcao/menuOpcao.png");
    env->canvas->draw(image.get(), 1, 0);
}

bool
Options::on_message(Object *object, MessageID id, Parameters)
{
    Environment *env = Environment::get_instance();

    if (id != Button::clickedID)
    {
        return false;
    }

    Button *button = dynamic_cast<Button *>(object);

    if (not button)
    {
        return false;
    }

    if (button->id() == "fullscreen")
    {
        env->video->set_fullscreen();
        set_next("options");
    } 
    else if (button->id() == "windowmode")
    {   
        
        env->video->set_fullscreen(false);
        set_next("options");
    }

    else if (button->id() == "back")
    {
        set_next("title");
    }

    finish();

    return true;
}
