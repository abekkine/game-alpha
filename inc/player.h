#ifndef PLAYER_H
#define PLAYER_H

#include <object.h>

class Player : public Object
{
    public:
        Player(double x, double y);
        ~Player();
        void Render();
        void MoveLeft();
        void MoveRight();
};

#endif

