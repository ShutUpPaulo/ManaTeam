/*
 * Exemplo de um objeto: um quadrado
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SQUARE_H
#define SQUARE_H

#include <core/object.h>
#include <core/keyboardevent.h>
#include <core/listener.h>

class Square : public Object, Listener
{
public:
    Square(Object *parent, ObjectID id, double size);
    ~Square();

    double size();
    bool on_event(const KeyboardEvent& event);

private:
    double m_speed;
    unsigned long m_last;

    void draw_self();
    void update_self(unsigned long elapsed);
};

#endif
