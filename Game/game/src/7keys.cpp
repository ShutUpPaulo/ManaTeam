/*
 * Implementação da classe SevenKeys.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include <ijengine/core/environment.h>

#include "7keys.h"
#include <ijengine/util/frontend.h>
#include "titlescreen.h"
#include "stage.h"

SevenKeys::SevenKeys()
    : Game("fone")
{
    Environment *env = Environment::get_instance();

    env->video->set_fullscreen();
}

Level *
SevenKeys::load_level(const string& id)
{   
    if (id == "fone")
    {
        return new FrontEnd("logo", "logo", "res/images/fone.png");
    }
    if (id == "logo")
    {
        return new FrontEnd("logo", "tecnologias", "res/images/logoMT.png");
    }
    else if (id == "tecnologias")
    {
        return new FrontEnd("tecnologias", "classificacao", "res/images/tecnologias.png");
    }cd
    else if (id == "classificacao")
    {
        return new FrontEnd("classificacao", "title", "res/images/classificacao_indicativa.png");
    } else if (id == "title")
    {
        return new TitleScreen();
    } else if (id == "stage1")
    {
        return new Stage("stage1");
    }

    return nullptr;
}
