/*
 * Implementação da classe SevenKeys.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <engine/environment.h>

#include "7keys.h"
#include "frontend.h"
#include "titlescreen.h"
#include "stage.h"

SevenKeys::SevenKeys()
    : Game("logo")
{
    Environment *env = Environment::get_instance();

    env->video->set_fullscreen();
}

Level *
SevenKeys::load_level(const string& id)
{
    if (id == "logo")
    {
        return new FrontEnd("tecnologias", "res/images/logoMT.png");
    }
    else if (id == "tecnologias")
    {
        return new FrontEnd("classificacao", "res/images/tecnologias.png");
    }
    else if (id == "classificacao")
    {
        return new FrontEnd("title", "res/images/classificacao_indicativa.png");
    } else if (id == "title")
    {
        return new TitleScreen();
    } else if (id == "stage1")
    {
        return new Stage("stage1");
    }

    return nullptr;
}
