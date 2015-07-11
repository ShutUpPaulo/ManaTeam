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
#include "options.h"

 #include <cstring>

SevenKeys::SevenKeys()
    : Game("fone")
{
    AudioManagerMusic * music2 = new AudioManagerMusic();
    music2 -> play("res/sounds/Key.ogg", -1);
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
        return new FrontEnd("logo", "tecnologias", "res/images/manateam.png");
    }
    else if (id == "tecnologias")
    {
        return new FrontEnd("tecnologias", "classificacao", "res/images/tecnologias.png");
    }
    else if (id == "classificacao")
    {
        return new FrontEnd("classificacao", "title", "res/images/classificacao_indicativa.png");
    } else if (id == "title")
    {
        return new TitleScreen();
    } else if (id == "options")
    {
        return new Options();
    }
    {

        if (strstr(id.c_str(), "stage"))
        {
            return new Stage(id);
        }
    }


    return nullptr;
}
