#ifndef PAUSE_H
#define PAUSE_H

#include <core/level.h>

class Image;

class Pause : public Level
{
public:
    Pause();
    virtual ~Pause();

    bool on_message(Object *sender, MessageID id, Parameters parameters);

private:
    void draw_self();
};

#endif