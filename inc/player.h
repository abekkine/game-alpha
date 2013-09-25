#ifndef PLAYER_H
#define PLAYER_H

#include <object.h>
#include <bullet.h>

class Player : public Object
{
    public:
        Player(double x, double y);
        ~Player();
        void Render();
        bool Alive();
        bool CollisionWith(Object* object);
        int Group();
        void Group(int group);
        Bullet* Fire();
        void MoveLeft();
        void MoveRight();
        Vector2 const& Position();
        double Size();
};

#endif

