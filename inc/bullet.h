#ifndef BULLET_H
#define BULLET_H

#include <object.h>

class Bullet : public Object
{
    public:
        Bullet(double x, double y);
        ~Bullet();
        void Group(int group);
        int Group();
        void Velocity(double vx, double vy);
        void Render();
        bool Alive();
        bool CollisionWith(Object* object);
        Vector2 const& Position();
        double Size();

    private:
        const double LIFE_MAX;
        const double LIFE_DELTA;
        double _life;
        int _group;
        double _vx;
        double _vy;
};

#endif

