#ifndef BULLET_H
#define BULLET_H

#include <object.h>

class Bullet : public Object
{
    public:
        Bullet(Vector2d position);
        ~Bullet();
        void Velocity(Vector2d velocity);
        void Render();
        bool CollisionWith(Object* object);

    private:
        const double LIFE_MAX;
        const double LIFE_DELTA;
        Vector2d _velocity;
};

#endif

