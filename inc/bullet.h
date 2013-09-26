#ifndef BULLET_H
#define BULLET_H

#include <object.h>

class Bullet : public Object
{
    public:
        Bullet(double x, double y);
        ~Bullet();
        void Velocity(double vx, double vy);
        void Render();
        bool CollisionWith(Object* object);

    private:
        const double LIFE_MAX;
        const double LIFE_DELTA;
        double _vx;
        double _vy;
};

#endif

