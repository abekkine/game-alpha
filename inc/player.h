#ifndef PLAYER_H
#define PLAYER_H

#include <object.h>
#include <bullet.h>

class Player : public Object
{
    public:
        Player(Vector2d position);
        ~Player();
        void Render();
        bool CollisionWith(Object* object);
        Bullet* Fire();
        void MoveLeft();
        void MoveRight();
        void RenderV1();
        void RenderV2();
};

#endif

