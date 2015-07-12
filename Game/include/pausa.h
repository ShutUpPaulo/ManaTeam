#ifndef PAUSA_H
#define PAUSA_H

#include <core/level.h>

class Image;

class Pausa : public Level
{
public:
    Pausa();
    virtual ~Pausa();

    bool on_message(Object *sender, MessageID id, Parameters parameters);

private:
    void draw_self();
};

#endif